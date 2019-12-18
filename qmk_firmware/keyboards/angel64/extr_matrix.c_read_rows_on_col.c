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
typedef  int matrix_row_t ;

/* Variables and functions */
 int MATRIX_ROWS ; 
 int ROW_SHIFTER ; 
 scalar_t__ readPin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * row_pins ; 
 int /*<<< orphan*/  select_col (int) ; 
 int /*<<< orphan*/  unselect_col (int) ; 
 int /*<<< orphan*/  wait_us (int) ; 

__attribute__((used)) static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col)
{
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    wait_us(30);

    // For each row...
    for(uint8_t row_index = 0; row_index < MATRIX_ROWS/2; row_index++)
    {
        uint8_t tmp = row_index + MATRIX_ROWS/2;
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[tmp];

        // Check row pin state
        if (readPin(row_pins[row_index]) == 0)
        {
            // Pin LO, set col bit
            current_matrix[tmp] |= (ROW_SHIFTER << current_col);
        }
        else
        {
            // Pin HI, clear col bit
            current_matrix[tmp] &= ~(ROW_SHIFTER << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[tmp]) && !(matrix_changed))
        {
            matrix_changed = true;
        }
    }

    // Unselect col
    unselect_col(current_col);

    return matrix_changed;
}