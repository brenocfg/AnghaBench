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
#define  BLANK 134 
#define  KC_CESC 133 
 int /*<<< orphan*/  KC_ESC ; 
 int /*<<< orphan*/  KC_LCTL ; 
 int /*<<< orphan*/  KC_SPC ; 
#define  LOWER 132 
 int /*<<< orphan*/  MOD_BIT (int /*<<< orphan*/ ) ; 
#define  PURE 131 
#define  QWERTY 130 
#define  RAISE 129 
#define  SPC_MOU 128 
 int /*<<< orphan*/  TAPPING_TERM ; 
 int /*<<< orphan*/  _ADJUST ; 
 int /*<<< orphan*/  _BLANK ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _MOUSE ; 
 int /*<<< orphan*/  _PURE ; 
 int /*<<< orphan*/  _QWERTY ; 
 int /*<<< orphan*/  _RAISE ; 
 int cntl_interrupted ; 
 int /*<<< orphan*/  cntl_timer ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int mouse_interrupted ; 
 int /*<<< orphan*/  mouse_timer ; 
 int /*<<< orphan*/  register_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  unregister_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case PURE:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_PURE);
          }
          return false;
          break;
        case BLANK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_BLANK);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;

        // BACKLIT is not used. If you want to use, uncomment below
        /*
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef __AVR__
            PORTE &= ~(1<<6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            PORTE |= (1<<6);
            #endif
          }
          return false;
          break;
        */

        case KC_CESC:
          if (record->event.pressed) {
           cntl_interrupted = false;
           cntl_timer = timer_read();
           register_mods(MOD_BIT(KC_LCTL));
          } else if (!cntl_interrupted && timer_elapsed(cntl_timer) < TAPPING_TERM) {
           unregister_mods(MOD_BIT(KC_LCTL));
           tap_code(KC_ESC);
          } else {
           unregister_mods(MOD_BIT(KC_LCTL));
          }
          return false;
          break;

        case SPC_MOU:
          if (record->event.pressed) {
           mouse_interrupted = false;
           mouse_timer = timer_read();

           cntl_interrupted = true;
           layer_on(_MOUSE);
          } else if (!mouse_interrupted && timer_elapsed(mouse_timer) < TAPPING_TERM) {
           layer_off(_MOUSE);
           tap_code(KC_SPC);
          } else {
           layer_off(_MOUSE);
          }
          return false;
          break;

        default:
          cntl_interrupted = true;
          mouse_interrupted = true;
          break;
      }
    return true;
}