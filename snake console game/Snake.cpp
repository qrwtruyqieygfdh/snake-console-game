#include <iostream>
#include <string>
#include<conio.h>
#include <thread>

using namespace std;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

bool gameOver;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    system("cls");
    //top border
    for (int i = 0; i < width + 1; i++) {
        cout << "#";
    }
    cout << endl;

    //left & right borders
    for (int i = 0; i < height; i++) {     //  OY
        for (int j = 0; j < width; j++) {  //  OX
            if (j == 0 || j == width - 1) {
                cout << "#";
            }
            if (i == y && j == x) {
                cout << "8";
            }
            else if (i == fruitY && j == fruitX) {
                cout << "F";
            }
            else {
                bool print_tail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "0";
                        print_tail = true;

                    }
                }
                if (!print_tail) {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    //bottom border
    for (int i = 0; i < width + 1; i++) {
        cout << "#";
    }
    cout << endl;

    //score
    cout << "SCORE " << score << endl;
    cout << "nTail " << nTail << endl;

}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    // snake tail
    tailX[0] = x;
    tailY[0] = y;
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // mooving
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }
    // dead if tail was ate
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    // borders teleport
    if (x >= width - 1) {
        x = 0;
    }
    if (x < 0) {
        x = width - 2;
    }
    if (y >= height) {
        y = 0;
    }
    if (y < 0) {
        y = height - 1;
    }
    // eating food
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    setlocale(0, "");
    Setup();

    while (gameOver == false) {
        Draw();
        Input();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

