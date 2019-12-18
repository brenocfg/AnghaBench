#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_7__ {int nkro; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
#define  PLOVER 130 
#define  QWERTY 129 
#define  WORKMAN 128 
 unsigned long _PLOVER ; 
 unsigned long _QWERTY ; 
 unsigned long _WORKMAN ; 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  eeconfig_is_enabled () ; 
 int /*<<< orphan*/  eeconfig_read_keymap () ; 
 int /*<<< orphan*/  eeconfig_update_keymap (int /*<<< orphan*/ ) ; 
 TYPE_4__ keymap_config ; 
 int /*<<< orphan*/  persistent_default_layer_set (unsigned long) ; 
 int /*<<< orphan*/  tone_plover ; 
 int /*<<< orphan*/  tone_qwerty ; 
 int /*<<< orphan*/  tone_workman ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case WORKMAN:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_workman);
        #endif
        persistent_default_layer_set(1UL<<_WORKMAN);
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_plover);
        #endif
        if (!eeconfig_is_enabled()) {
          eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
        persistent_default_layer_set(1UL<<_PLOVER);
      }
      return false;
      break;
  }
  return true;
}