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

/* Variables and functions */
 int MATRIX_COLS ; 
 int MATRIX_ROWS ; 
 int /*<<< orphan*/  debounce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  matrix ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int /*<<< orphan*/  raw_matrix ; 
 int read_cols_on_row (int /*<<< orphan*/ ,int) ; 
 int read_rows_on_col (int /*<<< orphan*/ ,int) ; 

uint8_t matrix_scan(void)
{
  bool changed = false;

  // Set row, read cols
  for (uint8_t current_row = 0; current_row < MATRIX_ROWS / 2; current_row++) {
    changed |= read_cols_on_row(raw_matrix, current_row);
  }
  //else
  // Set col, read rows
  for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
    changed |= read_rows_on_col(raw_matrix, current_col);
  }

  debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

  matrix_scan_quantum();
  return (uint8_t)changed;
}