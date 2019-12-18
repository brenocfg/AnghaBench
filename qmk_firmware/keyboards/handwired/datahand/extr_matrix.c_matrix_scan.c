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
 scalar_t__ MATRIX_ROWS ; 
 int /*<<< orphan*/  _delay_us (int) ; 
 int /*<<< orphan*/ * matrix ; 
 int /*<<< orphan*/  matrix_scan_user () ; 
 int /*<<< orphan*/  read_cols () ; 
 int /*<<< orphan*/  select_row (scalar_t__) ; 

uint8_t matrix_scan(void) {
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    select_row(row);
    /* The default hardware works down to at least 100us, but I have a replacement
     * photodiode that responds a little more slowly. Cranking it up to 1000us fixes
     * shadowing issues.
     */
    _delay_us(1000);
    matrix[row] = read_cols();
  }

  matrix_scan_user();

  return 1;
}