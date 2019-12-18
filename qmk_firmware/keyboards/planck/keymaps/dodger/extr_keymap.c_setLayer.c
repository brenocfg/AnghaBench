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

/* Variables and functions */
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
 int _COLEMAK ; 
 int _GAME ; 
 int _MUSIC ; 
 int /*<<< orphan*/  backlight_set (int) ; 
 int /*<<< orphan*/  guitar ; 
 int /*<<< orphan*/  mario ; 
 int /*<<< orphan*/  marioe ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int) ; 
 int /*<<< orphan*/  stop_all_notes () ; 

void setLayer(int layer) {
    if (layer == _COLEMAK) {
        #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(marioe);
        #endif
        set_single_persistent_default_layer(_COLEMAK);
        #ifdef BACKLIGHT_ENABLE
            backlight_set(0);
        #endif
    } else if (layer == _GAME) {
        #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(mario);
        #endif
        set_single_persistent_default_layer(_GAME);
        #ifdef BACKLIGHT_ENABLE
            backlight_set(15);
        #endif
    } else if (layer == _MUSIC) {
        #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(guitar);
        #endif
        set_single_persistent_default_layer(_MUSIC);
        #ifdef BACKLIGHT_ENABLE
            backlight_set(1);
        #endif
    }
}