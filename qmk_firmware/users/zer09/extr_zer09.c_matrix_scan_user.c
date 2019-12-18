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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_lyr ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  matrix_scan_keymap () ; 
 int rainbow_loop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_set () ; 
 int set_layer_led (int /*<<< orphan*/ ) ; 
 int shifted_layer () ; 

void matrix_scan_user(void) {
  static uint8_t is_leds_changes = 1;
  c_lyr = biton32(layer_state);

  is_leds_changes = is_leds_changes << set_layer_led(c_lyr);
  is_leds_changes = is_leds_changes << shifted_layer();
  is_leds_changes = is_leds_changes << rainbow_loop(c_lyr);

  if (is_leds_changes > 1) {
    rgblight_set();
    is_leds_changes = 1;
  }

  matrix_scan_keymap();
}