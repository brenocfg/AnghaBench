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
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
#define  SONG_GB 130 
#define  SONG_SC 129 
#define  SONG_SU 128 
 int /*<<< orphan*/  music_scale ; 
 int /*<<< orphan*/  tone_goodbye ; 
 int /*<<< orphan*/  tone_startup ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SONG_SU:
      if (record->event.pressed) {
        PLAY_SONG(tone_startup);
      }

      return false;

    case SONG_SC:
      if (record->event.pressed) {
        PLAY_SONG(music_scale);
      }

      return false;

    case SONG_GB:
      if (record->event.pressed) {
        PLAY_SONG(tone_goodbye);
      }

      return false;

    default:
      return true;
  }
}