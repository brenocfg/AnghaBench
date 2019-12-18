#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
#define  _OVERWATCH 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_mods () ; 
 int /*<<< orphan*/  combo_disable () ; 
 int /*<<< orphan*/  combo_enable () ; 
 int /*<<< orphan*/  layer_state_set_rgb (int /*<<< orphan*/ ) ; 

uint32_t layer_state_set_user(uint32_t state) {
  #ifdef RGBLIGHT_ENABLE
    layer_state_set_rgb(state);
  #endif
  uint8_t layer = biton32(state);
  combo_enable(); // by default, enable combos.
  switch (layer) {
    case 0:
      break;
    case 1:
      clear_mods();
      break;
    case 2:
      clear_mods();
      break;
    case _OVERWATCH:
      clear_mods();
      combo_disable(); // We don't want combos in overwatch
      #ifdef AUDIO_ENABLE
        // PLAY_SONG(song_overwatch);
      #endif
      break;
    default:
      break;
  }
  return state;
}