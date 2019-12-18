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
 scalar_t__* matrix ; 
 scalar_t__* matrix_debouncing ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 scalar_t__ read_rows () ; 
 int /*<<< orphan*/  select_col (scalar_t__) ; 
 int /*<<< orphan*/  unselect_cols () ; 

uint8_t matrix_scan(void) {
  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    select_col(col);
    _delay_us(3);
    uint8_t rows = read_rows();
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
      bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1<<col);
      bool curr_bit = rows & (1<<row);
      if (prev_bit != curr_bit) {
        matrix_debouncing[row] ^= ((matrix_row_t)1<<col);
        debouncing = DEBOUNCE;
      }
    }
    unselect_cols();
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