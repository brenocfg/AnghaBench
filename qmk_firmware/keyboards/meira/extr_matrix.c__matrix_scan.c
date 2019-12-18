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
 scalar_t__ MATRIX_COLS ; 
 scalar_t__ MATRIX_ROWS ; 
 int debouncing ; 
 int /*<<< orphan*/  debouncing_time ; 
 int /*<<< orphan*/ * matrix ; 
 int /*<<< orphan*/ * matrix_debouncing ; 
 int read_rows_on_col (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 

uint8_t _matrix_scan(void)
{
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

#   if (DEBOUNCE > 0)
        if (debouncing && (timer_elapsed(debouncing_time) > DEBOUNCE)) {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
            debouncing = false;
        }
#   endif

	return 1;
}