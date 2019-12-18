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

/* Variables and functions */
 scalar_t__ MATRIX_COLS ; 
 scalar_t__ ROWS_PER_HAND ; 
 int /*<<< orphan*/  debounce (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 scalar_t__ matrix ; 
 int /*<<< orphan*/  raw_matrix ; 
 int read_cols_on_row (int /*<<< orphan*/ ,scalar_t__) ; 
 int read_rows_on_col (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ thisHand ; 

uint8_t _matrix_scan(void) {
  bool changed = false;

#if defined(DIRECT_PINS) || (DIODE_DIRECTION == COL2ROW)
  // Set row, read cols
  for (uint8_t current_row = 0; current_row < ROWS_PER_HAND; current_row++) {
    changed |= read_cols_on_row(raw_matrix, current_row);
  }
#elif (DIODE_DIRECTION == ROW2COL)
  // Set col, read rows
  for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
    changed |= read_rows_on_col(raw_matrix, current_col);
  }
#endif

  debounce(raw_matrix, matrix + thisHand, ROWS_PER_HAND, changed);

  return 1;
}