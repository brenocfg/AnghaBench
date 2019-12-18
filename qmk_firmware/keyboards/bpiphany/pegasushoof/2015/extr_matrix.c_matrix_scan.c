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
 scalar_t__ MATRIX_COLS ; 
 int /*<<< orphan*/  debounce (scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  matrix ; 
 scalar_t__* matrix_debouncing ; 
 scalar_t__ matrix_rows () ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 scalar_t__ read_cols () ; 
 int /*<<< orphan*/  select_row (scalar_t__) ; 
 int /*<<< orphan*/  wait_us (int) ; 

uint8_t matrix_scan(void)
{
  bool changed = false;
  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    select_row(col);
    wait_us(30);
    matrix_row_t rows = read_cols();
    for (uint8_t row = 0; row < matrix_rows(); row++) {
      bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1<<col);
      bool curr_bit = rows & (1<<row);
      if ((changed |= prev_bit != curr_bit)) {
	    matrix_debouncing[row] ^= (matrix_row_t) 1 << col;
      }
    }
  }

  debounce(matrix_debouncing, matrix, matrix_rows(), changed);
  matrix_scan_quantum();

  return (uint8_t)changed;
}