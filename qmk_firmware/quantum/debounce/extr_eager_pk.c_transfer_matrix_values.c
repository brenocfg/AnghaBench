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
typedef  size_t uint8_t ;
typedef  int matrix_row_t ;
typedef  scalar_t__ debounce_counter_t ;

/* Variables and functions */
 scalar_t__ DEBOUNCE_ELAPSED ; 
 size_t MATRIX_COLS ; 
 size_t ROW_SHIFTER ; 
 int counters_need_update ; 
 scalar_t__* debounce_counters ; 
 int matrix_need_update ; 

void transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, uint8_t current_time) {
    matrix_need_update                   = false;
    debounce_counter_t *debounce_pointer = debounce_counters;
    for (uint8_t row = 0; row < num_rows; row++) {
        matrix_row_t delta        = raw[row] ^ cooked[row];
        matrix_row_t existing_row = cooked[row];
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            matrix_row_t col_mask = (ROW_SHIFTER << col);
            if (delta & col_mask) {
                if (*debounce_pointer == DEBOUNCE_ELAPSED) {
                    *debounce_pointer    = current_time;
                    counters_need_update = true;
                    existing_row ^= col_mask;  // flip the bit.
                } else {
                    matrix_need_update = true;
                }
            }
            debounce_pointer++;
        }
        cooked[row] = existing_row;
    }
}