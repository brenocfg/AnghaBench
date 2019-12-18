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
 int /*<<< orphan*/  KC_NUMLOCK ; 
 int /*<<< orphan*/  dynamic_macro_load_eeprom_all () ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void keyboard_post_init_user(void) {
  /* Customise these values to desired behaviour */
  //debug_enable = true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;

#ifdef DYNAMIC_MACRO_EEPROM_STORAGE
  /* Restore macros from eeprom */
  dynamic_macro_load_eeprom_all();
#endif

  /* Send numlock keycode to attempt to force numlock back on. */
  register_code(KC_NUMLOCK);
  unregister_code(KC_NUMLOCK);
}