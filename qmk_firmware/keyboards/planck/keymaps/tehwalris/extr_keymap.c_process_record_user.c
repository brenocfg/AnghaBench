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
 int /*<<< orphan*/  KC_A ; 
#define  KC_LSFT 132 
 int /*<<< orphan*/  KC_O ; 
#define  KC_RSFT 131 
 int /*<<< orphan*/  KC_U ; 
#define  UMLT_A 130 
#define  UMLT_O 129 
#define  UMLT_U 128 
 int /*<<< orphan*/  is_left_shift_pressed ; 
 int /*<<< orphan*/  is_right_shift_pressed ; 
 int /*<<< orphan*/  press_umlaut_of (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LSFT:
      is_left_shift_pressed = record->event.pressed;
      break;
    case KC_RSFT:
      is_right_shift_pressed = record->event.pressed;
      break;
    case UMLT_A:
      if (record->event.pressed) {
        press_umlaut_of(KC_A);
      }
      break;
    case UMLT_O:
      if (record->event.pressed) {
        press_umlaut_of(KC_O);
      }
      break;
    case UMLT_U:
      if (record->event.pressed) {
        press_umlaut_of(KC_U);
      }
      break;
  }
  return true;
}