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
typedef  int /*<<< orphan*/  macro_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_POWER ; 
 int /*<<< orphan*/  KC_RCTL ; 
 int /*<<< orphan*/  KC_RSFT ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int /*<<< orphan*/  PLAY_NOTE_ARRAY (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ADJUST ; 
 int /*<<< orphan*/  _FKEYS ; 
 int /*<<< orphan*/  _NUMSYM ; 
 int /*<<< orphan*/  _PLOVER ; 
 int /*<<< orphan*/  backlight_step () ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_all_notes () ; 
 int /*<<< orphan*/  tone_adjust ; 
 int /*<<< orphan*/  tone_plover ; 
 int /*<<< orphan*/  tone_qwerty ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 5: // MACSLEEP
            if (record->event.pressed) {
              register_code(KC_RSFT);
              register_code(KC_RCTL);
              register_code(KC_POWER);
              unregister_code(KC_POWER);
              unregister_code(KC_RCTL);
              unregister_code(KC_RSFT);
            }
        break;
        case 6: // PLOVER
              if (record->event.pressed) {
              #ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_NOTE_ARRAY(tone_plover, false, 0);
              #endif
              layer_off(_NUMSYM);
              layer_off(_FKEYS);
              layer_off(_ADJUST);
              layer_on(_PLOVER);
            }
        break;
        case 7: // LAYERRESET
              if (record->event.pressed) {
              #ifdef AUDIO_ENABLE
                PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
              #endif
              layer_off(_NUMSYM);
              layer_off(_FKEYS);
              layer_off(_PLOVER);
              layer_off(_ADJUST);
            }
        break;
        case 8: // BACKLIT
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
        case 9: // ADJUST
          if(record->event.pressed) {
            #ifdef AUDIO_ENABLE
              stop_all_notes();
              PLAY_NOTE_ARRAY(tone_adjust, false, 0);
            #endif
            layer_off(_NUMSYM);
            layer_off(_FKEYS);
            layer_off(_PLOVER);
            layer_on(_ADJUST);
          }
      }
    return MACRO_NONE;
}