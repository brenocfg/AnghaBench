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
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_SPC ; 
#define  UC_LNX 130 
#define  UC_OSX 129 
#define  UC_WIN 128 
 int get_unicode_input_mode () ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saved_mods ; 
 int /*<<< orphan*/  set_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void unicode_input_finish (void) {
  switch(get_unicode_input_mode()) {
    case UC_OSX:
    case UC_WIN:
      unregister_code(KC_LALT);
      break;
    case UC_LNX:
      register_code(KC_SPC);
      unregister_code(KC_SPC);
      break;
  }

  set_mods(saved_mods); // Reregister previously set mods
}