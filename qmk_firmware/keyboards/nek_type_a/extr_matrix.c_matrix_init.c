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

/* Variables and functions */
 size_t MATRIX_ROWS ; 
 int /*<<< orphan*/  OUTPUT_AUTO ; 
 int /*<<< orphan*/  init_cols () ; 
 int /*<<< orphan*/  init_rows () ; 
 scalar_t__* matrix ; 
 scalar_t__* matrix_debouncing ; 
 int /*<<< orphan*/  matrix_init_quantum () ; 
 int /*<<< orphan*/  set_output (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unselect_cols () ; 
 int /*<<< orphan*/  unselect_rows () ; 

void matrix_init(void) {
    // initialize row and col
#if (DIODE_DIRECTION == COL2ROW)
    unselect_rows();
    init_cols();
#elif (DIODE_DIRECTION == ROW2COL)
    unselect_cols();
    init_rows();
#endif

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

    matrix_init_quantum();
    set_output(OUTPUT_AUTO);
}