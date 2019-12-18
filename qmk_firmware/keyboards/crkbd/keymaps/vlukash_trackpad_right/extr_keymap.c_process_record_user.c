#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_9__ {int /*<<< orphan*/  buttons; } ;
typedef  TYPE_2__ report_mouse_t ;
struct TYPE_8__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_10__ {TYPE_1__ event; } ;
typedef  TYPE_3__ keyrecord_t ;
struct TYPE_11__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
#define  LOWER 134 
#define  MBTN1 133 
 int /*<<< orphan*/  MOUSE_BTN1 ; 
#define  QWERTY 132 
#define  RAISE 131 
#define  RGBRST 130 
#define  RGB_MOD 129 
 int /*<<< orphan*/  RGB_current_mode ; 
#define  SCRL 128 
 int /*<<< orphan*/  _ADJUST ; 
 int /*<<< orphan*/  _LOWER ; 
 unsigned long _QWERTY ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  eeconfig_update_rgblight_default () ; 
 int isScrollMode ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  persistent_default_layer_set (unsigned long) ; 
 TYPE_2__ pointing_device_get_report () ; 
 int /*<<< orphan*/  pointing_device_send () ; 
 int /*<<< orphan*/  pointing_device_set_report (TYPE_2__) ; 
 TYPE_4__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  rgblight_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_step () ; 
 int /*<<< orphan*/  update_tri_layer_RGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  report_mouse_t currentReport = {};
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case MBTN1:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN1;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN1;
      }
      pointing_device_set_report(currentReport);
      pointing_device_send();
      return false;
    case SCRL:
      if (record->event.pressed) {
        isScrollMode = true;
      }
      else {
        isScrollMode = false;
      }
      return false;
  }
  return true;
}