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
typedef  int uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  ESC_GRV 128 
 int /*<<< orphan*/  KC_ESC ; 
 int /*<<< orphan*/  KC_GRV ; 
 int /*<<< orphan*/  KC_LGUI ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_key (int /*<<< orphan*/ ) ; 
 int get_mods () ; 
 int /*<<< orphan*/  send_keyboard_report () ; 

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t esc_grv_mask;
  switch (id) {
    case ESC_GRV:
      esc_grv_mask = get_mods() & MOD_BIT(KC_LGUI);
      if (record->event.pressed) {
        if (esc_grv_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (esc_grv_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}