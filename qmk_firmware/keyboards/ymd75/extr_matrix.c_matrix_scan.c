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
typedef  scalar_t__ matrix_row_t ;

/* Variables and functions */
 scalar_t__ DEBOUNCE ; 
 scalar_t__ MATRIX_ROWS ; 
 int PINA ; 
 int PINC ; 
 int PIND ; 
 int PIND7 ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  _delay_us (int) ; 
 int bit_reverse (int) ; 
 scalar_t__ debouncing ; 
 scalar_t__* matrix ; 
 scalar_t__* matrix_debouncing ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int /*<<< orphan*/  matrix_set_row_status (scalar_t__) ; 

uint8_t matrix_scan(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_set_row_status(row);
        _delay_us(5);

        matrix_row_t cols = (
            // cols 0..7, PORTA 0 -> 7
            (~PINA) & 0xFF
        ) | (
            // cols 8..13, PORTC 7 -> 0
            bit_reverse((~PINC) & 0xFF) << 8
        ) | (
                  // col 14, PORTD 7
                  ((~PIND) & (1 << PIND7)) << 7
                  );

        if (matrix_debouncing[row] != cols) {
            matrix_debouncing[row] = cols;
            debouncing = DEBOUNCE;
        }
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }
    matrix_scan_quantum();  // also missing in original PS2AVRGB implementation
    //matrix_scan_user();

    return 1;
}