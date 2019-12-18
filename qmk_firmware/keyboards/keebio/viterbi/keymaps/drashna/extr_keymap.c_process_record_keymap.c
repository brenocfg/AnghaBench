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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  keyrecord_t ;

/* Variables and functions */

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {

  //switch (keycode) {
  //case KC_P00:
  //  if (!record->event.pressed) {
  //    tap(KC_KP_0);
  //    tap(KC_KP_0);
  //  }
  //  return false;
  //  break;
  //}
  return true;
}