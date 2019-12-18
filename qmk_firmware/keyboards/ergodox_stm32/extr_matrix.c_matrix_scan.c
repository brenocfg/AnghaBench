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

/* Variables and functions */
 size_t MATRIX_ROWS_PER_SIDE ; 
 int /*<<< orphan*/  debounce_read_cols (size_t) ; 
 int /*<<< orphan*/  ergodox_blink_all_leds () ; 
 scalar_t__ init_mcp23017 () ; 
 int /*<<< orphan*/ * matrix ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 scalar_t__ mcp23017_reset_loop ; 
 scalar_t__ mcp23017_status ; 
 int /*<<< orphan*/  select_row (size_t) ; 
 int /*<<< orphan*/  unselect_rows () ; 

uint8_t matrix_scan(void) {
  if (mcp23017_status) {
    if (++mcp23017_reset_loop == 0) {
      mcp23017_status = init_mcp23017();
        if (!mcp23017_status) {
            ergodox_blink_all_leds();
        }
    }
  }
  for (uint8_t i = 0; i < MATRIX_ROWS_PER_SIDE; i++) {
    select_row(i);
    select_row(i + MATRIX_ROWS_PER_SIDE);

    matrix[i] = debounce_read_cols(i);
    matrix[i + MATRIX_ROWS_PER_SIDE] = debounce_read_cols(i + MATRIX_ROWS_PER_SIDE);

    unselect_rows();
  }
  matrix_scan_quantum();
  return 0;
}