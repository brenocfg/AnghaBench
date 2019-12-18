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
 int /*<<< orphan*/  KC_RALT ; 
 int /*<<< orphan*/  KC_RCTL ; 
 int /*<<< orphan*/  KC_RGUI ; 
 int /*<<< orphan*/  KC_RSFT ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
#define  _COLEMAK 138 
#define  _DVORAK 137 
#define  _FCT 136 
#define  _LIN 135 
#define  _LOWER 134 
#define  _MAC 133 
#define  _MICMUTE 132 
#define  _OS 131 
#define  _QWERTY 130 
#define  _RAISE 129 
 int /*<<< orphan*/  _SETUP ; 
#define  _WIN 128 
 int currentOs ; 
 int /*<<< orphan*/  layer_off (int const) ; 
 int /*<<< orphan*/  layer_on (int const) ; 
 int /*<<< orphan*/  persistent_default_layer_set (unsigned long) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tone_colemak ; 
 int /*<<< orphan*/  tone_dvorak ; 
 int /*<<< orphan*/  tone_qwerty ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int const,int const,int /*<<< orphan*/ ) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case _QWERTY:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_qwerty);
            #endif
            persistent_default_layer_set(1UL<<_QWERTY);
          }
          break;
        case _COLEMAK:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_colemak);
            #endif
            persistent_default_layer_set(1UL<<_COLEMAK);
          }
          break;
        case _DVORAK:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_dvorak);
            #endif
            persistent_default_layer_set(1UL<<_DVORAK);
          }
          break;
        case _LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _SETUP);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _SETUP);
          }
          break;
        case _RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _SETUP);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _SETUP);
          }
          break;
        case _FCT:
          if (record->event.pressed) {
            layer_on(_FCT);
          } else {
            layer_off(_FCT);
          }
        break;
        case _MICMUTE:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            register_code(KC_RCTL);
            register_code(KC_RALT);
            register_code(KC_RGUI);
          } else {
            unregister_code(KC_RSFT);
            unregister_code(KC_RCTL);
            unregister_code(KC_RALT);
            unregister_code(KC_RGUI);
          }
        break;
        case _OS:
          if (record->event.pressed) {
            layer_on(currentOs);
          } else {
            layer_off(_MAC);
            layer_off(_WIN);
            layer_off(_LIN);
          }
        break;
        case _MAC:
        case _WIN:
        case _LIN:
          if (record->event.pressed) {
            layer_off(currentOs);
            currentOs = id;
          }
        break;
      }
    return MACRO_NONE;
}