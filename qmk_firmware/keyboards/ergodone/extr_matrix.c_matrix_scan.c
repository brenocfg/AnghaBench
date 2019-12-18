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
typedef  int matrix_row_t ;

/* Variables and functions */
 scalar_t__ MATRIX_ROWS ; 
 int debounce_mask (scalar_t__) ; 
 int /*<<< orphan*/  debounce_report (int,scalar_t__) ; 
 int /*<<< orphan*/  expander_scan () ; 
 int* matrix ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int read_cols (scalar_t__) ; 
 int /*<<< orphan*/  select_row (scalar_t__) ; 
 int /*<<< orphan*/  unselect_rows () ; 
 int /*<<< orphan*/  wait_us (int) ; 

uint8_t matrix_scan(void)
{
  expander_scan();

  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    select_row(i);
    wait_us(30);  // without this wait read unstable value.
    matrix_row_t mask = debounce_mask(i);
    matrix_row_t cols = (read_cols(i) & mask) | (matrix[i] & ~mask);
    debounce_report(cols ^ matrix[i], i);
    matrix[i] = cols;

    unselect_rows();
  }

  matrix_scan_quantum();

  return 1;
}