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
 int /*<<< orphan*/  GPIOD ; 
 int MATRIX_ROWS ; 
 int debouncing ; 
 int /*<<< orphan*/  debouncing_time ; 
 int* matrix ; 
 int* matrix_debouncing ; 
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
            case 0: palSetPad(GPIOB, 11);    break;
            case 1: palSetPad(GPIOB, 10);    break;
            case 2: palSetPad(GPIOB, 2);   	break;
            case 3: palSetPad(GPIOB, 1);   break;
            case 4: palSetPad(GPIOB, 0);    break;
        }

        wait_us(20); // need wait to settle pin state

        // read col data: { PTA15, PTC10, PTC11, PTC12, PTD2, PTB3, PTB4, PTB5, PTB6, PTB7, PTB8, PTB9, PTA2, PTA3 }
        data = ((palReadPort(GPIOA) & 0x8000UL) >> 15) |	// 0
        	   ((palReadPort(GPIOC) & 0x1C00UL) >> 9) |		// 1, 2, 3
			   ((palReadPort(GPIOD) & 0x0004UL) << 2) |		// 4
			   ((palReadPort(GPIOB) & 0x03F8UL) << 2) |		// 5, 6, 7, 8, 9, 10, 11
			   ((palReadPort(GPIOA) & 0x000CUL) << 10);    // 12, 13

        // un-strobe row
        switch (row) {
        	case 0: palClearPad(GPIOB, 11);    break;
        	case 1: palClearPad(GPIOB, 10);    break;
        	case 2: palClearPad(GPIOB, 2);	  break;
        	case 3: palClearPad(GPIOB, 1);   break;
        	case 4: palClearPad(GPIOB, 0);    break;
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
    return 1;
}