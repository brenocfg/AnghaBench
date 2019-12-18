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
 int /*<<< orphan*/  MATRIX_ROWS ; 
 scalar_t__ MATRIX_ROWS_PER_SIDE ; 
 int /*<<< orphan*/  debounce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ergodox_blink_all_leds () ; 
 scalar_t__ ergodox_left_leds_update () ; 
 scalar_t__ init_mcp23018 () ; 
 int /*<<< orphan*/  matrix ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 scalar_t__ mcp23018_reset_loop ; 
 scalar_t__ mcp23018_status ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  raw_matrix ; 
 int /*<<< orphan*/  select_row (scalar_t__) ; 
 int store_raw_matrix_row (scalar_t__) ; 
 int /*<<< orphan*/  unselect_rows () ; 

uint8_t matrix_scan(void) {
  if (mcp23018_status) {  // if there was an error
    if (++mcp23018_reset_loop == 0) {
      // if (++mcp23018_reset_loop >= 1300) {
      // since mcp23018_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
      // this will be approx bit more frequent than once per second
      print("trying to reset mcp23018\n");
      mcp23018_status = init_mcp23018();
      if (mcp23018_status) {
        print("left side not responding\n");
      } else {
        print("left side attached\n");
        ergodox_blink_all_leds();
      }
    }
  }

#ifdef LEFT_LEDS
  mcp23018_status = ergodox_left_leds_update();
#endif  // LEFT_LEDS
  bool changed = false;
  for (uint8_t i = 0; i < MATRIX_ROWS_PER_SIDE; i++) {
    // select rows from left and right hands
    uint8_t left_index = i;
    uint8_t right_index = i + MATRIX_ROWS_PER_SIDE;
    select_row(left_index);
    select_row(right_index);

    // we don't need a 30us delay anymore, because selecting a
    // left-hand row requires more than 30us for i2c.

    changed |= store_raw_matrix_row(left_index);
    changed |= store_raw_matrix_row(right_index);

    unselect_rows();
  }

  debounce(raw_matrix, matrix, MATRIX_ROWS, changed);
  matrix_scan_quantum();

  return 1;
}