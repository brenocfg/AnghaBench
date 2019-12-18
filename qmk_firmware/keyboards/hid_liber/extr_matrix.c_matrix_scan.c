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
 scalar_t__ MATRIX_COLS ; 
 scalar_t__ MATRIX_ROWS ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  _delay_us (int) ; 
 scalar_t__ debouncing ; 
 int /*<<< orphan*/  dprintf (char*,scalar_t__) ; 
 int* matrix ; 
 int* matrix_debouncing ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int /*<<< orphan*/  pull_column (scalar_t__) ; 
 int /*<<< orphan*/  release_column (scalar_t__) ; 
 int* row_bit ; 
 int** row_pin ; 

uint8_t matrix_scan(void)
{
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {  // 0-7
        pull_column(col);   // output hi on theline
        _delay_us(5);       // without this wait it won't read stable value.
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {  // 0-17
            bool prev_bit = matrix_debouncing[row] & (1<<col);
            bool curr_bit = *row_pin[row] & row_bit[row];
            if (prev_bit != curr_bit) {
                matrix_debouncing[row] ^= ((matrix_row_t)1<<col);
                if (debouncing) {
                    dprintf("bounce!: %02X\n", debouncing);
                }
                debouncing = DEBOUNCE;
            }
        }
        release_column(col);
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

    matrix_scan_quantum();
    return 1;
}