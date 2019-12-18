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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_LCTRL ; 
 int /*<<< orphan*/  KC_LGUI ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int MOD_MASK_ALT ; 
 int MOD_MASK_CTRL ; 
 int MOD_MASK_GUI ; 
 int MOD_MASK_SHIFT ; 
 int get_mods () ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void tap_with_modifiers(uint16_t keycode, uint8_t force_modifiers) {
  uint8_t active_modifiers = get_mods();

  if ((force_modifiers & MOD_MASK_SHIFT) && !(active_modifiers & MOD_MASK_SHIFT)) register_code(KC_LSFT);
  if ((force_modifiers & MOD_MASK_CTRL) && !(active_modifiers & MOD_MASK_CTRL)) register_code(KC_LCTRL);
  if ((force_modifiers & MOD_MASK_ALT) && !(active_modifiers & MOD_MASK_ALT)) register_code(KC_LALT);
  if ((force_modifiers & MOD_MASK_GUI) && !(active_modifiers & MOD_MASK_GUI)) register_code(KC_LGUI);

  register_code(keycode);
  unregister_code(keycode);

  if ((force_modifiers & MOD_MASK_SHIFT) && !(active_modifiers & MOD_MASK_SHIFT)) unregister_code(KC_LSFT);
  if ((force_modifiers & MOD_MASK_CTRL) && !(active_modifiers & MOD_MASK_CTRL)) unregister_code(KC_LCTRL);
  if ((force_modifiers & MOD_MASK_ALT) && !(active_modifiers & MOD_MASK_ALT)) unregister_code(KC_LALT);
  if ((force_modifiers & MOD_MASK_GUI) && !(active_modifiers & MOD_MASK_GUI)) unregister_code(KC_LGUI);
}