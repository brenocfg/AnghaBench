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
 int /*<<< orphan*/  SEND_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_TAP (int /*<<< orphan*/ ) ; 
 int USB_LED_NUM_LOCK ; 
 int /*<<< orphan*/  X_NUMLOCK ; 
 int host_keyboard_leds () ; 

void matrix_init_user(void) {
  // set num lock on at start independently of state (for numonly layer to work)
  if (!(host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) {
      SEND_STRING(SS_TAP(X_NUMLOCK)); //register_code(KC_NUMLOCK); unregister_code(KC_NUMLOCK);
  }
}