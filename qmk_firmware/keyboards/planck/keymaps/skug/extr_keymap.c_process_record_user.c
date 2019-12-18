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
#define  BACKLIT 138 
#define  DEFAULT 137 
 int /*<<< orphan*/  KC_RSFT ; 
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
 int PORTE ; 
#define  S1 136 
#define  S2 135 
#define  S3 134 
#define  S4 133 
#define  S5 132 
#define  S6 131 
#define  S7 130 
#define  S8 129 
#define  S9 128 
 int /*<<< orphan*/  _DEFAULT ; 
 int /*<<< orphan*/  backlight_step () ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s1 ; 
 int /*<<< orphan*/  s2 ; 
 int /*<<< orphan*/  s3 ; 
 int /*<<< orphan*/  s4 ; 
 int /*<<< orphan*/  s5 ; 
 int /*<<< orphan*/  s6 ; 
 int /*<<< orphan*/  s7 ; 
 int /*<<< orphan*/  s8 ; 
 int /*<<< orphan*/  s9 ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DEFAULT:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DEFAULT);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
        #endif
      }
      return false;
      break;
    case S1:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s1);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
    case S2:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s2);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
    case S3:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s3);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
    case S4:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s4);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
    case S5:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s5);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
    case S6:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s6);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
    case S7:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s7);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
    case S8:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s8);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
    case S9:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s9);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
  }
  return true;
}