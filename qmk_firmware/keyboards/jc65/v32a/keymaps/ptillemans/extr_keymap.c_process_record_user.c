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
 int /*<<< orphan*/  KC_GRV ; 
#define  KC_HASH 128 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shift_pressed () ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  static bool tilde_pressed = false;

  switch (keycode) {
  case KC_HASH:
    if (shift_pressed()) {
      if (record->event.pressed) {
        tilde_pressed = true;
        register_code(KC_GRV);
        return false;
      }
      else if (tilde_pressed) {
        unregister_code(KC_GRV);
        tilde_pressed = false;
        return false;
      }
    }
    return true;
  default:
    return true; // Process all other keycodes normally
  }
}