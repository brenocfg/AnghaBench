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
 int /*<<< orphan*/  c_lyr ; 
 scalar_t__ led_brightness (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int process_record_keymap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rgblight_set () ; 
 int /*<<< orphan*/  set_key_led (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  set_key_led(record, c_lyr);

  if (led_brightness(keycode, record)) {
    rgblight_set();
    return false;
  }

  rgblight_set();
  return process_record_keymap(keycode, record);
}