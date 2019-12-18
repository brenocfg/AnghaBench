#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  ALT_TAB 129 
 int /*<<< orphan*/  KC_LALT ; 
#define  KC_LAST 128 
 int /*<<< orphan*/  KC_LCTRL ; 
 int /*<<< orphan*/  KC_TAB ; 
 int /*<<< orphan*/  MOD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 void* alt_tab_timer ; 
 int is_alt_tab_active ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_mods (int /*<<< orphan*/ ) ; 
 int timer_elapsed (int) ; 
 void* timer_read () ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_mods (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t macro_timer;

  switch (keycode) {
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }

  switch (keycode){
    case KC_LAST:
      if(record->event.pressed){
        macro_timer = timer_read();
        register_mods(MOD_BIT(KC_LCTRL));
      } else {
        unregister_mods(MOD_BIT(KC_LCTRL));
        if (timer_elapsed(macro_timer) < 150) {
          SEND_STRING("!$");
        }
      }
    return false;
  }
  return true;
}