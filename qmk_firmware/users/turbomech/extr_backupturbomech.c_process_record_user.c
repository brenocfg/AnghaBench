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
#define  KC_MAKE_ALU84 131 
#define  KC_QMK 130 
#define  KC_RESET 129 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 char* SS_TAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X_ENTER ; 
#define  _QWERTY 128 
 int /*<<< orphan*/  persistent_default_layer_set (unsigned long) ; 
 int process_record_keymap (int,TYPE_2__*) ; 
 int /*<<< orphan*/  reset_keyboard () ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  rgblight_setrgb (int,int,int) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case _QWERTY:
      persistent_default_layer_set(1UL << _QWERTY);
      return false;
      break;
    case KC_MAKE_ALU84:
      if (!record->event.pressed) {
        SEND_STRING("make alu84:TurboMech:dfu");
        SEND_STRING(SS_TAP(X_ENTER));
    }
    return false;
    break;
    case KC_QMK:
      if (!record->event.pressed) {
        SEND_STRING("cd QMK/qmk_firmware");
        SEND_STRING(SS_TAP(X_ENTER));
      }
      return false;
      break;
    case KC_RESET:
      if (!record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_setrgb(255, 255, 255);
        #endif
        //_delay_ms(2000);
        reset_keyboard();
      }
      return false;
      break;
    /*case RGB_MOD:
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
      if (record->event.pressed) {
       rgblight_mode(RGB_current_mode);
       RGB_current_mode = rgblight_config.mode;
        rgblight_step();
       // rgblight_mode(RGB_current_mode);
     //RGB_current_mode = rgblight_config.mode;
        // _delay_ms(50);
       // rgblight_set();
        RGB_current_mode = rgblight_config.mode;
    }
      else //if (rgblight_config.enable)
      {
        _delay_ms(50);
        rgblight_set();
        //rgblight_mode(rgblight_config.mode);
      // eeconfig_update_rgblight(rgblight_config.raw);
      }

     return true;
      break;*/

    /*case MO(1):
      if (record->event.realeased) {
        rgblight_mode(1);
        rgblight_set_red;
      }
      return true;
      break;*/

   /*case KC_CAPS:
     if (record->event.pressed) {
        rgblight_mode(RGB_current_mode);
       register_code(KC_CAPS);
        rgblight_mode(1);
        rgblight_set_red;
      }
      else {
        unregister_code(KC_CAPS);
        rgblight_mode(RGB_current_mode);

      }
      return false;
       break;*/

       /* rgblight_mode(RGB_current_mode);
        register_code(KC_CAPS);
        rgblight_mode(1);
        rgblight_set_red;
      }
      else {
        unregister_code(KC_CAPS);
        rgblight_mode(RGB_current_mode);*/

    //  }
    //  return true;
     //  break;
    /*case KC_RESET:
      if (record->event.pressed) {
      layer_off(_FUNCTION);
      rgblight_mode(RGB_current_mode);
     RGB_current_mode = rgblight_config.mode;
      layer_clear();
      _delay_ms(1000);
        reset_keyboard();
     }
     else{
      //layer_off(_FUNCTION);
     _delay_ms(1000);
     rgblight_mode(RGB_current_mode);
     RGB_current_mode = rgblight_config.mode;

     //eeconfig_update_rgblight_default();
      }

      return false;
      break;
    }*/


      return true;
      break;





/*case RGB_MOD:
case RGB_HUI:
case RGB_HUD:
case RGB_SAI:
case RGB_SAD:
case RGB_VAI:
case RGB_VAD:
case RGB_MODE_PLAIN:
case RGB_MODE_BREATHE:
case RGB_MODE_RAINBOW:
case RGB_MODE_SWIRL:
case RGB_MODE_SNAKE:
case RGB_MODE_KNIGHT:
case RGB_MODE_XMAS:
case RGB_MODE_GRADIENT:
    if (record->event.pressed) {
      rgb_layer_change = false;
    }
    break;
  }
  return true;*/
  }


 return process_record_keymap(keycode, record);

}