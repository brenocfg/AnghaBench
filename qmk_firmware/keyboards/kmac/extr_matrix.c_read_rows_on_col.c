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
typedef  size_t matrix_row_t ;

/* Variables and functions */
 int /*<<< orphan*/  E2 ; 
 size_t MATRIX_ROWS ; 
 size_t ROW_SHIFTER ; 
 scalar_t__ readPin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * row_pins ; 
 int /*<<< orphan*/  select_col (size_t) ; 
 int /*<<< orphan*/  unselect_cols () ; 
 int /*<<< orphan*/  wait_us (int) ; 

__attribute__((used)) static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    wait_us(30);

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        // Check row pin state
        // Use the otherwise unused row: 3, col: 0 for caps lock
        if (row_index == 3 && current_col == 0) {
            if (readPin(E2) == 0) {
                // Pin LO, set col bit
                current_matrix[row_index] |= (ROW_SHIFTER << current_col);
            } else {
                // Pin HI, clear col bit
                current_matrix[row_index] &= ~(ROW_SHIFTER << current_col);
            }
        } else {
            if (readPin(row_pins[row_index]) == 0) {
                // Pin HI, clear col bit
                current_matrix[row_index] &= ~(ROW_SHIFTER << current_col);
            } else {
                // Pin LO, set col bit
                current_matrix[row_index] |= (ROW_SHIFTER << current_col);
            }
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[row_index]) && !(matrix_changed)) {
            matrix_changed = true;
        }
    }

    // Unselect cols
    unselect_cols();

    return matrix_changed;
}