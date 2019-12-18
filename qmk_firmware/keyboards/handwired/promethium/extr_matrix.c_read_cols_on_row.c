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
 size_t MATRIX_COLS ; 
 size_t ROW_SHIFTER ; 
 size_t _BV (size_t) ; 
 size_t _SFR_IO8 (size_t) ; 
 int /*<<< orphan*/  _delay_us (int) ; 
 size_t* col_pins ; 
 int /*<<< orphan*/  select_row (size_t) ; 
 size_t* tp_pins ; 
 int /*<<< orphan*/  unselect_row (size_t) ; 

__attribute__((used)) static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row)
    {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[current_row];

        // Clear data in matrix row
        current_matrix[current_row] = 0;

        // special case for trackpoint
        if (current_row == 8) {
            for(uint8_t tp_index = 0; tp_index < 3; tp_index++) {

                // Select the TP pin to read (active low)
                uint8_t pin = tp_pins[tp_index];
                uint8_t pin_state = (_SFR_IO8(pin >> 4) & _BV(pin & 0xF));

                // Populate the matrix row with the state of the col pin
                current_matrix[current_row] |=  pin_state ? 0 : (ROW_SHIFTER << tp_index);
            }
            return (last_row_value != current_matrix[current_row]);
        }

        // Select row and wait for row selecton to stabilize
        select_row(current_row);
        _delay_us(5);       // without this wait it won't read stable value.
        // wait_us(50);

        // For each col...
        for(uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {

            // Select the col pin to read (active low)
            uint8_t pin = col_pins[col_index];
            uint8_t pin_state = (_SFR_IO8(pin >> 4) & _BV(pin & 0xF));

            // Populate the matrix row with the state of the col pin
            current_matrix[current_row] |=  pin_state ? 0 : (ROW_SHIFTER << col_index);
        }

        // Unselect row
        unselect_row(current_row);

        return (last_row_value != current_matrix[current_row]);
}