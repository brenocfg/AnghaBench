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
#define  BACKLIT 132 
#define  COLEMAK 131 
 int /*<<< orphan*/  KC_RSFT ; 
#define  LOWER 130 
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
#define  QWERTY 129 
#define  RAISE 128 
 int /*<<< orphan*/  _ADJUST ; 
 unsigned long _COLEMAK ; 
 int /*<<< orphan*/  _LOWER ; 
 unsigned long _QWERTY ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  backlight_step () ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  persistant_default_layer_set (unsigned long) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tone_colemak ; 
 int /*<<< orphan*/  tone_qwerty ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistant_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    /*case DVORAK:*/
      /*if (record->event.pressed) {*/
        /*#ifdef AUDIO_ENABLE*/
          /*PLAY_SONG(tone_dvorak);*/
        /*#endif*/
        /*persistant_default_layer_set(1UL<<_DVORAK);*/
      /*}*/
      /*return false;*/
      /*break;*/
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
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    /*case PLOVER:*/
      /*if (record->event.pressed) {*/
        /*#ifdef AUDIO_ENABLE*/
          /*stop_all_notes();*/
          /*PLAY_SONG(tone_plover);*/
        /*#endif*/
        /*layer_off(_RAISE);*/
        /*layer_off(_LOWER);*/
        /*layer_off(_ADJUST);*/
        /*layer_on(_PLOVER);*/
        /*if (!eeconfig_is_enabled()) {*/
            /*eeconfig_init();*/
        /*}*/
        /*keymap_config.raw = eeconfig_read_keymap();*/
        /*keymap_config.nkro = 1;*/
        /*eeconfig_update_keymap(keymap_config.raw);*/
      /*}*/
      /*return false;*/
      /*break;*/
    /*case EXT_PLV:*/
      /*if (record->event.pressed) {*/
        /*#ifdef AUDIO_ENABLE*/
          /*PLAY_SONG(tone_plover_gb);*/
        /*#endif*/
        /*layer_off(_PLOVER);*/
      /*}*/
      /*return false;*/
      /*break;*/
  }
  return true;
}