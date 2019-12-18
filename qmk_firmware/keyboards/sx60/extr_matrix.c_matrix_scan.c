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
 scalar_t__ MATRIX_ROWS ; 
 int debouncing ; 
 int /*<<< orphan*/  debouncing_time ; 
 scalar_t__ init_mcp23018 () ; 
 int /*<<< orphan*/ * matrix ; 
 int /*<<< orphan*/ * matrix_debouncing ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 scalar_t__ mcp23018_reset_loop ; 
 scalar_t__ mcp23018_status ; 
 int /*<<< orphan*/  print (char*) ; 
 int read_cols_on_row (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 

uint8_t matrix_scan(void)
{
    if (mcp23018_status) {
        /* if there was an error */
        if (++mcp23018_reset_loop == 0) {
            /* since mcp23018_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
               this will be approx bit more frequent than once per second */
            print("trying to reset mcp23018\n");
            mcp23018_status = init_mcp23018();
            if (mcp23018_status) {
                print("left side not responding\n");
            } else {
                print("left side attached\n");
            }
        }
    }

    /* Set row, read cols */
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

#   if (DEBOUNCE > 0)
        if (debouncing && (timer_elapsed(debouncing_time) > DEBOUNCE)) {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
            debouncing = false;
        }
#   endif

    matrix_scan_quantum();
    return 1;
}