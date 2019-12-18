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
 int /*<<< orphan*/ * matrix ; 
 int /*<<< orphan*/ * matrix_debounce ; 
 int matrix_read (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 

uint8_t matrix_scan(void) { 
    for ( uint8_t current_row = 0; current_row < MATRIX_ROWS; ++current_row ) {
#       if (DEBOUNCE > 0)
            bool matrix_changed = matrix_read(matrix_debounce, current_row);
            
            if (matrix_changed) {
                debouncing      = true        ;
                debouncing_time = timer_read();
            }
                        
#       else
            matrix_read(matrix, current_row);
#       endif
    }
    
#   if (DEBOUNCE > 0)
        if (debouncing && (timer_elapsed(debouncing_time) > DEBOUNCE)) {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debounce[i];
            }
            debouncing = false;
        }
#   endif

    matrix_scan_quantum();
    return 1;
}