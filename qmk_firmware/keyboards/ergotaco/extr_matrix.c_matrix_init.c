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
 size_t MATRIX_COLS ; 
 size_t MATRIX_ROWS ; 
 scalar_t__* debounce_matrix ; 
 int /*<<< orphan*/  init_cols () ; 
 int /*<<< orphan*/  init_mcp23018 () ; 
 scalar_t__* matrix ; 
 int /*<<< orphan*/  matrix_init_quantum () ; 
 int /*<<< orphan*/  mcp23018_status ; 
 scalar_t__* raw_matrix ; 
 int /*<<< orphan*/  unselect_rows () ; 

void matrix_init(void)
{
    // initialize row and col
    mcp23018_status = init_mcp23018();
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        raw_matrix[i] = 0;
        for (uint8_t j=0; j < MATRIX_COLS; ++j) {
            debounce_matrix[i * MATRIX_COLS + j] = 0;
        }
    }

    matrix_init_quantum();
}