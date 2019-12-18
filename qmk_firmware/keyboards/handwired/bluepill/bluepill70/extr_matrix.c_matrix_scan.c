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
 scalar_t__ debouncing ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug_hex (scalar_t__) ; 
 scalar_t__* matrix ; 
 scalar_t__* matrix_debouncing ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 scalar_t__ read_cols () ; 
 int /*<<< orphan*/  select_row (scalar_t__) ; 
 int /*<<< orphan*/  unselect_rows () ; 
 int /*<<< orphan*/  wait_ms (int) ; 
 int /*<<< orphan*/  wait_us (int) ; 

uint8_t matrix_scan(void){
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    select_row(i);
    wait_us(30);  // without this wait read unstable value.
    matrix_row_t cols = read_cols();
    if (matrix_debouncing[i] != cols) {
      matrix_debouncing[i] = cols;
      if (debouncing) {
        debug("bounce!: "); debug_hex(debouncing); debug("\n");
      }
    debouncing = DEBOUNCE;
    }
    unselect_rows();
  }

  if (debouncing) {
    if (--debouncing) {
      wait_ms(1);
    } else {
      for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = matrix_debouncing[i];
      }
    }
  }
  matrix_scan_quantum();
  return 1;
}