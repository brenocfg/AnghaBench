#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_7__ {int mode; } ;

/* Variables and functions */
#define  ADJUST 134 
#define  BL_STEP 133 
#define  BL_TOGG 132 
#define  LOWER 131 
 int /*<<< orphan*/  PLAY_NOTE_ARRAY (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
#define  QWERTY 130 
#define  RAISE 129 
#define  RGB_MOD 128 
 int RGB_current_mode ; 
 int TOG_STATUS ; 
 int /*<<< orphan*/  _ADJUST ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  backlight_step () ; 
 int /*<<< orphan*/  issi_init () ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print (char*) ; 
 TYPE_3__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  rgblight_step () ; 
 int /*<<< orphan*/  tone_qwerty ; 
 int /*<<< orphan*/  update_tri_layer_RGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
//        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
        if (record->event.pressed) {
            //not sure how to have keyboard check mode and set it to a variable, so my work around
            //uses another variable that would be set to true after the first time a reactive key is pressed.
            if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
            } else {
                TOG_STATUS = !TOG_STATUS;
#ifdef RGBLIGHT_ENABLE
                rgblight_mode(16);
#endif
            }
            layer_on(_LOWER);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        } else {
#ifdef RGBLIGHT_ENABLE
            rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
#endif
            TOG_STATUS = false;
            layer_off(_LOWER);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
    case RAISE:
        if (record->event.pressed) {
            //not sure how to have keyboard check mode and set it to a variable, so my work around
            //uses another variable that would be set to true after the first time a reactive key is pressed.
            if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
            } else {
                TOG_STATUS = !TOG_STATUS;
#ifdef RGBLIGHT_ENABLE
                rgblight_mode(15);
#endif
            }
            layer_on(_RAISE);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        } else {
#ifdef RGBLIGHT_ENABLE
            rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
#endif
            layer_off(_RAISE);
            TOG_STATUS = false;
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
    case ADJUST:
        // FIXME add RGB feedback
        if (record->event.pressed) {
            layer_on(_ADJUST);
        } else {
            layer_off(_ADJUST);
        }
        return false;
        break;
    case BL_TOGG:
#ifdef ISSI_ENABLE
        if (record->event.pressed) {
            print("Enabling backlight\n");
            issi_init();
        }
#endif
        return false;
        break;
    case BL_STEP:
        if (record->event.pressed) {
            print("Stepping backlight\n");
#ifdef BACKLIGHT_ENABLE
            print("Really stepping backlight\n");
            backlight_step();
#endif

        }
        return false;
        break;
        //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
#ifdef RGBLIGHT_ENABLE
    case RGB_MOD:
        if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
        }
        return false;
        break;
#endif
//    case BL_INC:
//    		meira_inc_backlight_level();
//    	      return false;
//    		break;
  }
  return true;
}