#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  LOCK 129 
 int /*<<< orphan*/  RGBLIGHT_MODE_RAINBOW_SWIRL ; 
#define  TAP_TOG_LAYER 128 
 int /*<<< orphan*/  _SYMB ; 
 int /*<<< orphan*/  process_tap_tog (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  rgblight_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_tog_count ; 
 int tap_tog_layer_other_key_pressed ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOCK:
      if (record->event.pressed) {
        rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
      }
      return true; // Let QMK send the press/release events
      break;

    case TAP_TOG_LAYER:
      process_tap_tog(_SYMB,record);
      return false;
      break;
    default:
      tap_tog_count = 0; // reset counter.
      tap_tog_layer_other_key_pressed = true; // always set this to true, TAP_TOG_LAYER handlers will handle interpreting this
      break;
  }
  return true;
}