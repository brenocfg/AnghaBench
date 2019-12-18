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
 scalar_t__ DEBOUNCE ; 
 int debouncing ; 
 int /*<<< orphan*/  debouncing_time ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 

void            debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
    if (changed) {
        debouncing      = true;
        debouncing_time = timer_read();
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int i = 0; i < num_rows; i++) {
            cooked[i] = raw[i];
        }
        debouncing = false;
    }
}