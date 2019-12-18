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
typedef  scalar_t__ debounce_counter_t ;

/* Variables and functions */
 scalar_t__ DEBOUNCE ; 
 scalar_t__ DEBOUNCE_ELAPSED ; 
 scalar_t__ MATRIX_COLS ; 
 int /*<<< orphan*/  MAX_DEBOUNCE ; 
 scalar_t__ TIMER_DIFF (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int counters_need_update ; 
 scalar_t__* debounce_counters ; 

void update_debounce_counters(uint8_t num_rows, uint8_t current_time) {
    counters_need_update                 = false;
    debounce_counter_t *debounce_pointer = debounce_counters;
    for (uint8_t row = 0; row < num_rows; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            if (*debounce_pointer != DEBOUNCE_ELAPSED) {
                if (TIMER_DIFF(current_time, *debounce_pointer, MAX_DEBOUNCE) >= DEBOUNCE) {
                    *debounce_pointer = DEBOUNCE_ELAPSED;
                } else {
                    counters_need_update = true;
                }
            }
            debounce_pointer++;
        }
    }
}