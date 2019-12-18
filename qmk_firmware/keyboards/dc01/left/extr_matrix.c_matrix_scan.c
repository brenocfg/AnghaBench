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
 scalar_t__ ERROR_DISCONNECT_COUNT ; 
 scalar_t__ MATRIX_COLS ; 
 scalar_t__ MATRIX_ROWS ; 
 int /*<<< orphan*/  SLAVE_I2C_ADDRESS_ARROW ; 
 int /*<<< orphan*/  SLAVE_I2C_ADDRESS_NUMPAD ; 
 int /*<<< orphan*/  SLAVE_I2C_ADDRESS_RIGHT ; 
 int debouncing ; 
 int /*<<< orphan*/  debouncing_time ; 
 scalar_t__ error_count_arrow ; 
 scalar_t__ error_count_numpad ; 
 scalar_t__ error_count_right ; 
 scalar_t__ i2c_transaction (int /*<<< orphan*/ ,int,int) ; 
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

    if (i2c_transaction(SLAVE_I2C_ADDRESS_RIGHT, 0x3F, 0)){ //error has occured for main right half
        error_count_right++;
        if (error_count_right > ERROR_DISCONNECT_COUNT){ //disconnect half
            for (uint8_t i = 0; i < MATRIX_ROWS ; i++) {
                matrix[i] &= 0x3F; //mask bits to keep
            }
        }
   }else{ //no error
        error_count_right = 0;
    }

    if (i2c_transaction(SLAVE_I2C_ADDRESS_ARROW, 0X3FFF, 8)){ //error has occured for arrow cluster
        error_count_arrow++;
        if (error_count_arrow > ERROR_DISCONNECT_COUNT){ //disconnect arrow cluster
            for (uint8_t i = 0; i < MATRIX_ROWS ; i++) {
                matrix[i] &= 0x3FFF; //mask bits to keep
            }
        }
    }else{ //no error
        error_count_arrow = 0;
    }

    if (i2c_transaction(SLAVE_I2C_ADDRESS_NUMPAD, 0x1FFFF, 11)){ //error has occured for numpad
        error_count_numpad++;
        if (error_count_numpad > ERROR_DISCONNECT_COUNT){ //disconnect numpad
            for (uint8_t i = 0; i < MATRIX_ROWS ; i++) {
                matrix[i] &= 0x1FFFF; //mask bits to keep
            }
        }
    }else{ //no error
        error_count_numpad = 0;
    }

    matrix_scan_quantum();
    return 1;
}