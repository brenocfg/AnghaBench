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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  BR_DOWN 129 
#define  BR_UP 128 
 int /*<<< orphan*/  KC_PAUS ; 
 int /*<<< orphan*/  KC_SLCK ; 
 int /*<<< orphan*/  MOD_RGUI ; 
 int /*<<< orphan*/  add_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_keyboard_report () ; 
 int /*<<< orphan*/  unregister_mods (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t key;
  switch (keycode) {
    case BR_DOWN:
    case BR_UP:
      // Clear the RGUI modifier placed by LM for _ML layer as brightness don't
      // work with modifiers.
      key = (keycode == BR_DOWN) ? KC_SLCK : KC_PAUS;
      if (record->event.pressed) {
          unregister_mods(MOD_RGUI);
          add_key(key);
          send_keyboard_report();
      } else {
          del_key(key);
          send_keyboard_report();
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}