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
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  GPIOC ; 
 int /*<<< orphan*/  GPIOD ; 
 int MATRIX_ROWS ; 
 int debouncing ; 
 int /*<<< orphan*/  debouncing_time ; 
 int* matrix ; 
 int* matrix_debouncing ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int /*<<< orphan*/  palClearPad (int /*<<< orphan*/ ,int) ; 
 int palReadPort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  palSetPad (int /*<<< orphan*/ ,int) ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  wait_us (int) ; 

uint8_t matrix_scan(void)
{
    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data = 0;
        // strobe row
        switch (row) {
            case 0: palSetPad(GPIOB, 2);    break;
            case 1: palSetPad(GPIOB, 3);    break;
            case 2: palSetPad(GPIOB, 18);   break;
            case 3: palSetPad(GPIOB, 19);   break;
            case 4: palSetPad(GPIOC, 0);    break;
            case 5: palSetPad(GPIOC, 8);    break;
            case 6: palSetPad(GPIOC, 9);    break;
            case 7: palSetPad(GPIOD, 0);    break;
            case 8: palSetPad(GPIOD, 1);    break;
            case 9: palSetPad(GPIOD, 4);    break;
        }

        // need wait to settle pin state
        // if you wait too short, or have a too high update rate
        // the keyboard might freeze, or there might not be enough
        // processing power to update the LCD screen properly.
        // 20us, or two ticks at 100000Hz seems to be OK
        wait_us(20);

        // read col data: { PTD5, PTD6, PTD7, PTC1, PTC2, PTC3, PTC4, PTC5, PTC6, PTC7 }
        data = ((palReadPort(GPIOC) & 0xFEUL) << 2) |
               ((palReadPort(GPIOD) & 0xE0UL) >> 5);

        // un-strobe row
        switch (row) {
            case 0: palClearPad(GPIOB, 2);  break;
            case 1: palClearPad(GPIOB, 3);  break;
            case 2: palClearPad(GPIOB, 18); break;
            case 3: palClearPad(GPIOB, 19); break;
            case 4: palClearPad(GPIOC, 0);  break;
            case 5: palClearPad(GPIOC, 8);  break;
            case 6: palClearPad(GPIOC, 9);  break;
            case 7: palClearPad(GPIOD, 0);  break;
            case 8: palClearPad(GPIOD, 1);  break;
            case 9: palClearPad(GPIOD, 4);  break;
        }

        if (matrix_debouncing[row] != data) {
            matrix_debouncing[row] = data;
            debouncing = true;
            debouncing_time = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            matrix[row] = matrix_debouncing[row];
        }
        debouncing = false;
    }

    matrix_scan_quantum();
    return 1;
}