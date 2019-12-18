#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_7__ {scalar_t__ pressed; } ;
struct TYPE_8__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  PLAY_SONG (float**) ; 
 int /*<<< orphan*/  UC_BSD ; 
 int /*<<< orphan*/  UC_LNX ; 
 int /*<<< orphan*/  UC_OSX ; 
 int /*<<< orphan*/  UC_WIN ; 
 int /*<<< orphan*/  UC_WINC ; 
#define  UNICODE_MODE_BSD 134 
#define  UNICODE_MODE_FORWARD 133 
#define  UNICODE_MODE_LNX 132 
#define  UNICODE_MODE_OSX 131 
#define  UNICODE_MODE_REVERSE 130 
#define  UNICODE_MODE_WIN 129 
#define  UNICODE_MODE_WINC 128 
 float** UNICODE_SONG_BSD ; 
 float** UNICODE_SONG_LNX ; 
 float** UNICODE_SONG_OSX ; 
 float** UNICODE_SONG_WIN ; 
 float** UNICODE_SONG_WINC ; 
 int /*<<< orphan*/  cycle_unicode_input_mode (int) ; 
 int process_ucis (int,TYPE_2__*) ; 
 int process_unicode (int,TYPE_2__*) ; 
 int process_unicodemap (int,TYPE_2__*) ; 
 int /*<<< orphan*/  set_unicode_input_mode (int /*<<< orphan*/ ) ; 

bool process_unicode_common(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case UNICODE_MODE_FORWARD:
                cycle_unicode_input_mode(+1);
                break;
            case UNICODE_MODE_REVERSE:
                cycle_unicode_input_mode(-1);
                break;

            case UNICODE_MODE_OSX:
                set_unicode_input_mode(UC_OSX);
#if defined(AUDIO_ENABLE) && defined(UNICODE_SONG_OSX)
                static float song_osx[][2] = UNICODE_SONG_OSX;
                PLAY_SONG(song_osx);
#endif
                break;
            case UNICODE_MODE_LNX:
                set_unicode_input_mode(UC_LNX);
#if defined(AUDIO_ENABLE) && defined(UNICODE_SONG_LNX)
                static float song_lnx[][2] = UNICODE_SONG_LNX;
                PLAY_SONG(song_lnx);
#endif
                break;
            case UNICODE_MODE_WIN:
                set_unicode_input_mode(UC_WIN);
#if defined(AUDIO_ENABLE) && defined(UNICODE_SONG_WIN)
                static float song_win[][2] = UNICODE_SONG_WIN;
                PLAY_SONG(song_win);
#endif
                break;
            case UNICODE_MODE_BSD:
                set_unicode_input_mode(UC_BSD);
#if defined(AUDIO_ENABLE) && defined(UNICODE_SONG_BSD)
                static float song_bsd[][2] = UNICODE_SONG_BSD;
                PLAY_SONG(song_bsd);
#endif
                break;
            case UNICODE_MODE_WINC:
                set_unicode_input_mode(UC_WINC);
#if defined(AUDIO_ENABLE) && defined(UNICODE_SONG_WINC)
                static float song_winc[][2] = UNICODE_SONG_WINC;
                PLAY_SONG(song_winc);
#endif
                break;
        }
    }
#if defined(UNICODE_ENABLE)
    return process_unicode(keycode, record);
#elif defined(UNICODEMAP_ENABLE)
    return process_unicodemap(keycode, record);
#elif defined(UCIS_ENABLE)
    return process_ucis(keycode, record);
#else
    return true;
#endif
}