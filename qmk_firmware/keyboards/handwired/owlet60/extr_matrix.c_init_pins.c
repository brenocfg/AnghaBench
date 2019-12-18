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

/* Variables and functions */
 int /*<<< orphan*/  dat_pin ; 
 int /*<<< orphan*/  setPinInputHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unselect_rows () ; 

__attribute__((used)) static void init_pins(void) {   // still need some fixing, this might not work
  unselect_rows();              // with the loop
  /*
  for (uint8_t x = 0; x < MATRIX_COLS; x++) {
    setPinInputHigh(col_pins[x]);
  }
  */
  setPinInputHigh(dat_pin);
}