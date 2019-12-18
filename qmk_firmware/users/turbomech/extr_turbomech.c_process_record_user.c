#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_7__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_8__ {int mode; } ;

/* Variables and functions */
#define  KC_CAPS 130 
#define  KC_RESET 129 
#define  RGB_MOD 128 
 int RGB_current_mode ; 
 int caps_is_active ; 
 int process_record_keymap (int,TYPE_2__*) ; 
 int /*<<< orphan*/  register_code (int const) ; 
 int /*<<< orphan*/  reset_keyboard () ; 
 TYPE_3__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  rgblight_setrgb (int,int,int) ; 
 int /*<<< orphan*/  rgblight_step () ; 
 int /*<<< orphan*/  unregister_code (int const) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_CAPS:
     if (record->event.pressed) {
        register_code(KC_CAPS);
        caps_is_active = !caps_is_active;
      if (caps_is_active) {
        rgblight_mode(14);
      }
      else if (!caps_is_active) {
        unregister_code(KC_CAPS);
        rgblight_mode(RGB_current_mode);
      }
    }
    return false;
    break;

    case RGB_MOD:
    //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    if (record->event.pressed) {
      rgblight_mode(RGB_current_mode);
      rgblight_step();
      RGB_current_mode = rgblight_config.mode;
      // rgblight_set();
    }
    return false;
    break;

    case KC_RESET:
    if (record->event.pressed) {
      rgblight_enable();
      rgblight_mode(1);
      rgblight_setrgb(255, 255, 255);
      //_delay_ms(2000);
      reset_keyboard();
    }
    return false;
    break;

    /*case _FLIP:  //(╯°□°）╯︵ ┻━┻
      if (record->event.pressed) {
       register_code(KC_LPRN);
       unregister_code(KC_LPRN);
       register_code(X(0x00B0));
       unregister_code(X(0x00B0));

        UC(0x256F);
        PROCESS_UNICODE(UC(0x00B0));
        SEND_TAP(UC(0x25A1));
        SEND_TAP(UC(0x00B0));
        SEND_STRING(")");
        SEND_TAP(UC(0x256F));
        SEND_TAP(UC(0xFE35));
        SEND_TAP(UC(0x253B));
        SEND_TAP(UC(0x2501));
        SEND_TAP(UC(0x253B));
			}
			return false;
			break;*/

  return true;
  break;
  }
return process_record_keymap(keycode, record);
}