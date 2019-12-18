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
 int /*<<< orphan*/  EZ_RGB (int) ; 
 int /*<<< orphan*/  KC_1 ; 
 int /*<<< orphan*/  KC_2 ; 
 int /*<<< orphan*/  KC_3 ; 
 int /*<<< orphan*/  KC_4 ; 
 int /*<<< orphan*/  KC_EQL ; 
#define  LED1 135 
#define  LED2 134 
#define  LED3 133 
#define  RGB_0000FF 132 
#define  RGB_00FF00 131 
#define  RGB_FF0000 130 
#define  RGB_FFFFFF 129 
#define  RGB_TOGGLE 128 
 int /*<<< orphan*/  ergodox_right_led_1_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_on () ; 
 int /*<<< orphan*/  ergodox_right_led_2_off () ; 
 int /*<<< orphan*/  ergodox_right_led_2_on () ; 
 int /*<<< orphan*/  ergodox_right_led_3_off () ; 
 int /*<<< orphan*/  ergodox_right_led_3_on () ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_toggle () ; 
 int status_led1_on ; 
 int status_led2_on ; 
 int status_led3_on ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case RGB_FF0000:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          EZ_RGB(0xff0000UL);
          register_code(KC_1); unregister_code(KC_1);
        #endif
      }
      return false;
      break;
    case RGB_00FF00:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          EZ_RGB(0x00ff00UL);
          register_code(KC_2); unregister_code(KC_2);
        #endif
      }
      return false;
      break;
    case RGB_0000FF:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          EZ_RGB(0x0000ffUL);
          register_code(KC_3); unregister_code(KC_3);
        #endif
      }
      return false;
      break;
    case RGB_FFFFFF:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          EZ_RGB(0xffffffUL);
          register_code(KC_4); unregister_code(KC_4);
        #endif
      }
      return false;
      break;
    case RGB_TOGGLE:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_toggle();
          register_code(KC_EQL); unregister_code(KC_EQL);
        #endif
      }
      return false;
      break;
    case LED1:
      if (record->event.pressed) {
        if(status_led1_on) {
        ergodox_right_led_1_off();
        status_led1_on = false;
        } else {
        ergodox_right_led_1_on();
        status_led1_on = true;
        }
      }
      return false;
      break;
    case LED2:
      if (record->event.pressed) {
        if(status_led2_on) {
        ergodox_right_led_2_off();
        status_led2_on = false;
        } else {
        ergodox_right_led_2_on();
        status_led2_on = true;
        }
      }
      return false;
      break;
    case LED3:
      if (record->event.pressed) {
        if(status_led3_on) {
        ergodox_right_led_3_off();
        status_led3_on = false;
        } else {
        ergodox_right_led_3_on();
        status_led3_on = true;
        }
      }
      return false;
      break;
  }
  return true;
}