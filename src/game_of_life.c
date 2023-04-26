#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // usleep(TIME);

#define GRID_HEIGHT 25
#define GRID_WIDTH 80
#define TIME 100000
#define MAX_ITER 10000

void compareGrid(int gridOne[GRID_HEIGHT][GRID_WIDTH], int gridTwo[GRID_HEIGHT][GRID_WIDTH]);
void determineState(int gridOne[GRID_HEIGHT][GRID_WIDTH]);
void printGrid(int gridOne[GRID_HEIGHT][GRID_WIDTH]);
int lives(int gridOne[GRID_HEIGHT][GRID_WIDTH]);
void clearScreen();

int main() {
    clearScreen();
    int gridOne[GRID_HEIGHT][GRID_WIDTH] = {0};
    int x, y, n;
    int start;
    int speed_amplifier;
    do {
        clearScreen();
        printf("Enter speed level (1 - slowest, 10 - fastest):  ");
        scanf("%d", &speed_amplifier);
    } while (!(speed_amplifier < 11 && speed_amplifier > 0));
    speed_amplifier = 11 - speed_amplifier;
    printf("Enter the number of cells: ");
    scanf("%d", &n);
    printGrid(gridOne);
    for (int i = 0; i < n; i++) {
        clearScreen();
        printGrid(gridOne);
        printf("Enter coordinates of %d cell: ", i + 1);
        scanf("%d %d", &x, &y);
        gridOne[x - 1][y - 1] = 1;
    }
    clearScreen();
    printGrid(gridOne);
    printf("Grid seetup is done. Start the game? (1/0)   ");
    scanf("%d", &start);
    if (start == 1) {
        int i = 0;
        do {
            printGrid(gridOne);
            determineState(gridOne);
            usleep(speed_amplifier * TIME);
            clearScreen();
            if (lives(gridOne) == 0) break;
            ++i;
        } while (i < MAX_ITER);
    }
    printGrid(gridOne);
    printf("This is the end of the game\n");
    return 0;
}

void compareGrid(int gridOne[GRID_HEIGHT][GRID_WIDTH], int gridTwo[GRID_HEIGHT][GRID_WIDTH]) {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            gridTwo[i][j] = gridOne[i][j];
        }
    }
}

void determineState(int gridOne[GRID_HEIGHT][GRID_WIDTH]) {
    int gridTwo[GRID_HEIGHT][GRID_WIDTH] = {0};
    compareGrid(gridOne, gridTwo);
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            int alive = 0;
            for (int c = -1; c < 2; c++) {
                for (int d = -1; d < 2; d++) {
                    if (!(c == 0 && d == 0)) {
                        int y = i + c;
                        int x = j + d;
                        if (y > GRID_HEIGHT - 1) y = 0;
                        if (x > GRID_WIDTH - 1) x = 0;
                        if (y < 0) y = GRID_HEIGHT - 1;
                        if (x < 0) x = GRID_WIDTH - 1;
                        if (gridTwo[y][x] == 1) ++alive;
                    }
                }
            }
            if (alive < 2) gridOne[i][j] = 0;
            if (alive == 3) gridOne[i][j] = 1;
            if (alive > 3) gridOne[i][j] = 0;
        }
    }
}

void printGrid(int gridOne[GRID_HEIGHT][GRID_WIDTH]) {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (gridOne[i][j] == 1) printf(" 0 ");
            if (gridOne[i][j] == 0) printf(" . ");
            if (j == GRID_WIDTH - 1) printf("\n");
        }
    }
}

int lives(int gridOne[GRID_HEIGHT][GRID_WIDTH]) {
    int l = 0;
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (gridOne[i][j] == 1) l++;
        }
    }
    return l;
}

void clearScreen() { printf("\33[0d\33[2J"); }
