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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ DEBOUNCE ; 
 scalar_t__ DEVICE_STATE_Configured ; 
 scalar_t__ MATRIX_COLS ; 
 scalar_t__ MATRIX_ROWS ; 
 scalar_t__ USB_DeviceState ; 
 int debouncing ; 
 int /*<<< orphan*/  debouncing_time ; 
 int* i2c_slave_reg ; 
 int* matrix ; 
 int* matrix_debouncing ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int read_cols_on_row (int*,scalar_t__) ; 
 int read_rows_on_col (int*,scalar_t__) ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 

uint8_t matrix_scan(void)
{
#if (DIODE_DIRECTION == COL2ROW)

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
#       if (DEBOUNCE > 0)
            bool matrix_changed = read_cols_on_row(matrix_debouncing, current_row);

            if (matrix_changed) {
                debouncing = true;
                debouncing_time = timer_read();
            }

#       else
            read_cols_on_row(matrix, current_row);
#       endif

    }

#elif (DIODE_DIRECTION == ROW2COL)

    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
#       if (DEBOUNCE > 0)
            bool matrix_changed = read_rows_on_col(matrix_debouncing, current_col);
            if (matrix_changed) {
                debouncing = true;
                debouncing_time = timer_read();
            }
#       else
             read_rows_on_col(matrix, current_col);
#       endif

    }

#endif

#   if (DEBOUNCE > 0)
        if (debouncing && (timer_elapsed(debouncing_time) > DEBOUNCE)) {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
            debouncing = false;
        }
#   endif

        if (USB_DeviceState != DEVICE_STATE_Configured){
            i2c_slave_reg[1] = 0x55;
            for (uint8_t i = 0; i < MATRIX_ROWS; i++){
                i2c_slave_reg[i+2] = matrix[i]; //send matrix over i2c
            }
        }

    matrix_scan_quantum();
    return 1;
}