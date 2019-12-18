#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int matrix_row_t ;

/* Variables and functions */
 scalar_t__ DEBOUNCE ; 
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  GPIOC ; 
 int MATRIX_COLS ; 
 int MATRIX_ROWS ; 
 int debouncing ; 
 int /*<<< orphan*/  debouncing_time ; 
 int* matrix ; 
 int* matrix_debouncing ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int /*<<< orphan*/  palClearPad (int /*<<< orphan*/ ,int) ; 
 int palReadPad (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  palSetPad (int /*<<< orphan*/ ,int) ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  wait_us (int) ; 

uint8_t matrix_scan(void) {
    // actual matrix
    for (int col = 0; col < MATRIX_COLS; col++) {
        matrix_row_t data = 0;

        // strobe col { PB10, PB2, PB1, PB0, PA7, PB4, PB3, PB7 }
        switch (col) {
            case 0: palSetPad(GPIOB, 10); break;
            case 1: palSetPad(GPIOB, 2); break;
            case 2: palSetPad(GPIOB, 1); break;
            case 3: palSetPad(GPIOB, 0); break;
            case 4: palSetPad(GPIOA, 7); break;
            case 5: palSetPad(GPIOB, 4); break;
            case 6: palSetPad(GPIOB, 3); break;
            case 7: palSetPad(GPIOB, 7); break;
        }

        // need wait to settle pin state
        wait_us(20);

        // read row data { PB11, PA6, PA3, PA2, PA1, PB5, PB6, PC15, PC14, PC13 }
        data = (
            (palReadPad(GPIOB, 11) << 0 ) |
            (palReadPad(GPIOA, 6)  << 1 ) |
            (palReadPad(GPIOA, 3)  << 2 ) |
            (palReadPad(GPIOA, 2) << 3 ) |
            (palReadPad(GPIOA, 1) << 4 ) |
            (palReadPad(GPIOB, 5) << 5 ) |
            (palReadPad(GPIOB, 6) << 6 ) |
            (palReadPad(GPIOC, 15)  << 7 ) |
            (palReadPad(GPIOC, 14)  << 8 ) |
            (palReadPad(GPIOC, 13)  << 9 )
        );

        // unstrobe  col { B11, B10, B2, B1, A7, B0 }
        switch (col) {
            case 0: palClearPad(GPIOB, 10); break;
            case 1: palClearPad(GPIOB, 2); break;
            case 2: palClearPad(GPIOB, 1); break;
            case 3: palClearPad(GPIOB, 0); break;
            case 4: palClearPad(GPIOA, 7); break;
            case 5: palClearPad(GPIOB, 4); break;
            case 6: palClearPad(GPIOB, 3); break;
            case 7: palClearPad(GPIOB, 7); break;
        }

        if (matrix_debouncing[col] != data) {
            matrix_debouncing[col] = data;
            debouncing = true;
            debouncing_time = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            matrix[row] = 0;
            for (int col = 0; col < MATRIX_COLS; col++) {
                matrix[row] |= ((matrix_debouncing[col] & (1 << row) ? 1 : 0) << col);
            }
        }
        debouncing = false;
    }

    matrix_scan_quantum();

    return 1;
}