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
#define  S_BSKTC 136 
#define  S_COIN 135 
#define  S_DOEDR 134 
#define  S_ODEJY 133 
#define  S_ONEUP 132 
#define  S_RCKBY 131 
#define  S_SCALE 130 
#define  S_SONIC 129 
#define  S_ZELDA 128 
 int /*<<< orphan*/  song_basketcase ; 
 int /*<<< orphan*/  song_coin ; 
 int /*<<< orphan*/  song_doe_a_deer ; 
 int /*<<< orphan*/  song_ode_to_joy ; 
 int /*<<< orphan*/  song_one_up ; 
 int /*<<< orphan*/  song_rock_a_bye_baby ; 
 int /*<<< orphan*/  song_scale ; 
 int /*<<< orphan*/  song_sonic_ring ; 
 int /*<<< orphan*/  song_zelda_puzzle ; 
 int /*<<< orphan*/  stop_all_notes () ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        #ifdef AUDIO_ENABLE
            case S_BSKTC:
                if (record->event.pressed) {
                    stop_all_notes();
                    PLAY_SONG(song_basketcase);
                }
                return false;
            case S_ODEJY:
                if (record->event.pressed) {
                    stop_all_notes();
                    PLAY_SONG(song_ode_to_joy);
                }
                return false;
            case S_RCKBY:
                if (record->event.pressed) {
                    stop_all_notes();
                    PLAY_SONG(song_rock_a_bye_baby);
                }
                return false;
            case S_DOEDR:
                if (record->event.pressed) {
                    stop_all_notes();
                    PLAY_SONG(song_doe_a_deer);
                }
                return false;
            case S_SCALE:
                if (record->event.pressed) {
                    stop_all_notes();
                    PLAY_SONG(song_scale);
                }
                return false;
            case S_ONEUP:
                if (record->event.pressed) {
                    stop_all_notes();
                    PLAY_SONG(song_one_up);
                }
                return false;
            case S_COIN:
                if (record->event.pressed) {
                    stop_all_notes();
                    PLAY_SONG(song_coin);
                }
                return false;
            case S_SONIC:
                if (record->event.pressed) {
                    stop_all_notes();
                    PLAY_SONG(song_sonic_ring);
                }
                return false;
            case S_ZELDA:
                if (record->event.pressed) {
                    stop_all_notes();
                    PLAY_SONG(song_zelda_puzzle);
                }
                return false;
        #endif
    }
    return true;
}