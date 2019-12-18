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
 scalar_t__ ROWS_PER_HAND ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  _delay_us (int) ; 
 scalar_t__ debouncing ; 
 scalar_t__ isLeftHand ; 
 scalar_t__* matrix ; 
 scalar_t__* matrix_debouncing ; 
 scalar_t__ read_cols () ; 
 int /*<<< orphan*/  select_row (scalar_t__) ; 
 int /*<<< orphan*/  unselect_rows () ; 

uint8_t _matrix_scan(void) {
  // Right hand is stored after the left in the matirx so, we need to offset it
  int offset = isLeftHand ? 0 : (ROWS_PER_HAND);

  for (uint8_t i = 0; i < ROWS_PER_HAND; i++) {
      select_row(i);
      _delay_us(30);  // without this wait read unstable value.
      matrix_row_t cols = read_cols();
      if (matrix_debouncing[i+offset] != cols) {
          matrix_debouncing[i+offset] = cols;
          debouncing = DEBOUNCE;
      }
      unselect_rows();
  }

  if (debouncing) {
      if (--debouncing) {
          _delay_ms(1);
      } else {
          for (uint8_t i = 0; i < ROWS_PER_HAND; i++) {
              matrix[i+offset] = matrix_debouncing[i+offset];
          }
      }
  }

  return 1;
}