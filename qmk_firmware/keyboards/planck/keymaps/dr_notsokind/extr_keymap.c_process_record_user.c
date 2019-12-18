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
#define  DYN_REC_START1 136 
#define  DYN_REC_START2 135 
#define  DYN_REC_STOP 134 
 int /*<<< orphan*/  IS_LAYER_ON (int /*<<< orphan*/ ) ; 
#define  LOWER 133 
#define  MEDIA 132 
#define  NUMPAD 131 
#define  ONESHOT 130 
 int /*<<< orphan*/  ONESHOT_PRESSED ; 
 int /*<<< orphan*/  ONESHOT_START ; 
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
#define  QWERTY 129 
#define  RAISE 128 
 int /*<<< orphan*/  _FUNCTN ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _MEDIA ; 
 int /*<<< orphan*/  _NUMPAD ; 
 int /*<<< orphan*/  _ONESHOT ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  clear_oneshot_layer_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_record_dynamic_macro (int,TYPE_2__*) ; 
 int /*<<< orphan*/  set_oneshot_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tone_dyn_macro_rec ; 
 int /*<<< orphan*/  tone_dyn_macro_stop ; 
 int /*<<< orphan*/  tone_numpad ; 
 int /*<<< orphan*/  tone_oneshot ; 
 int /*<<< orphan*/  tone_qwerty ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // uint16_t macro_kc = (keycode == ONESHOT ? DYN_REC_STOP : keycode);
    if (!process_record_dynamic_macro(keycode, record)) {
        switch(keycode) {
          case DYN_REC_START1:
          case DYN_REC_START2:
#ifdef AUDIO_ENABLE
              PLAY_SONG(tone_dyn_macro_rec);
#endif
              break;
          case DYN_REC_STOP:
#ifdef AUDIO_ENABLE
              PLAY_SONG(tone_dyn_macro_stop);
#endif
              break;
        }
        return false;
    }
    switch (keycode) {
        case ONESHOT:
            if (record->event.pressed) {
                layer_on(_ONESHOT);
                set_oneshot_layer(_ONESHOT, ONESHOT_START);
                clear_oneshot_layer_state(ONESHOT_PRESSED);
#ifdef AUDIO_ENABLE
                PLAY_SONG(tone_oneshot);
#endif
            }
            return false;
            break;
        case QWERTY:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_NUMPAD)) {
#ifdef AUDIO_ENABLE
                    PLAY_SONG(tone_qwerty);
#endif
                    layer_off(_NUMPAD);
                }
            }
            return false;
            break;
        case NUMPAD:
            if (record->event.pressed) {
                if (!IS_LAYER_ON(_NUMPAD)) {
#ifdef AUDIO_ENABLE
                    PLAY_SONG(tone_numpad);
#endif
                    layer_on(_NUMPAD);
                }
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_RAISE, _LOWER, _FUNCTN);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_RAISE, _LOWER, _FUNCTN);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_RAISE, _LOWER, _FUNCTN);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_RAISE, _LOWER, _FUNCTN);
            }
            return false;
            break;
        case MEDIA:
            if (record->event.pressed) {
                layer_on(_MEDIA);
            } else {
                layer_off(_MEDIA);
            }
            return false;
            break;
    }
    return true;
}