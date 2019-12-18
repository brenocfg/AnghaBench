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
 scalar_t__ IS_LAYER_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _GAME ; 
 int /*<<< orphan*/  gh60_wasd_leds_off () ; 
 int /*<<< orphan*/  gh60_wasd_leds_on () ; 

void matrix_scan_user(void) {
  #ifdef KEYBOARD_gh60
    if (IS_LAYER_ON(_GAME)) {
      gh60_wasd_leds_on();
    } else {
      gh60_wasd_leds_off();
    }
  #endif
}