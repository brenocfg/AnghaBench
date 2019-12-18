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
typedef  int /*<<< orphan*/  matrix_row_t ;

/* Variables and functions */
 int MAX_DEBOUNCE ; 
 scalar_t__ counters_need_update ; 
 scalar_t__ matrix_need_update ; 
 int timer_read () ; 
 int /*<<< orphan*/  transfer_matrix_values (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  update_debounce_counters (int,int) ; 

void debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
    uint8_t current_time = timer_read() % MAX_DEBOUNCE;
    if (counters_need_update) {
        update_debounce_counters(num_rows, current_time);
    }

    if (changed || matrix_need_update) {
        transfer_matrix_values(raw, cooked, num_rows, current_time);
    }
}