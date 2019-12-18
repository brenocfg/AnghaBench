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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bootloader_jump () ; 
 int /*<<< orphan*/  clear_keyboard () ; 
 int /*<<< orphan*/  goodbye_song ; 
 int /*<<< orphan*/  haptic_shutdown () ; 
 int /*<<< orphan*/  music_all_notes_off () ; 
 int /*<<< orphan*/  process_midi_all_notes_off () ; 
 int /*<<< orphan*/  shutdown_user () ; 
 int /*<<< orphan*/  stop_all_notes () ; 
 int timer_elapsed (int) ; 
 int timer_read () ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void reset_keyboard(void) {
    clear_keyboard();
#if defined(MIDI_ENABLE) && defined(MIDI_BASIC)
    process_midi_all_notes_off();
#endif
#ifdef AUDIO_ENABLE
#    ifndef NO_MUSIC_MODE
    music_all_notes_off();
#    endif
    uint16_t timer_start = timer_read();
    PLAY_SONG(goodbye_song);
    shutdown_user();
    while (timer_elapsed(timer_start) < 250) wait_ms(1);
    stop_all_notes();
#else
    shutdown_user();
    wait_ms(250);
#endif
#ifdef HAPTIC_ENABLE
    haptic_shutdown();
#endif
// this is also done later in bootloader.c - not sure if it's neccesary here
#ifdef BOOTLOADER_CATERINA
    *(uint16_t *)0x0800 = 0x7777;  // these two are a-star-specific
#endif
    bootloader_jump();
}