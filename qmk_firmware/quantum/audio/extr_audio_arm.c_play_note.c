#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPTD8 ; 
 int /*<<< orphan*/  RESTART_CHANNEL_1 () ; 
 int /*<<< orphan*/  RESTART_CHANNEL_2 () ; 
 TYPE_1__ audio_config ; 
 int /*<<< orphan*/  audio_init () ; 
 int /*<<< orphan*/  audio_initialized ; 
 int /*<<< orphan*/  dprintf (char*,int,int) ; 
 scalar_t__ envelope_index ; 
 float* frequencies ; 
 int /*<<< orphan*/  gpt8cfg1 ; 
 int /*<<< orphan*/  gptStart (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gptStartContinuous (int /*<<< orphan*/ *,unsigned int) ; 
 int playing_note ; 
 scalar_t__ playing_notes ; 
 int /*<<< orphan*/  stop_all_notes () ; 
 int voices ; 
 int* volumes ; 

void play_note(float freq, int vol) {
    dprintf("audio play note freq=%d vol=%d", (int)freq, vol);

    if (!audio_initialized) {
        audio_init();
    }

    if (audio_config.enable && voices < 8) {
        // Cancel notes if notes are playing
        if (playing_notes) {
            stop_all_notes();
        }

        playing_note = true;

        envelope_index = 0;

        if (freq > 0) {
            frequencies[voices] = freq;
            volumes[voices]     = vol;
            voices++;
        }

        gptStart(&GPTD8, &gpt8cfg1);
        gptStartContinuous(&GPTD8, 2U);
        RESTART_CHANNEL_1();
        RESTART_CHANNEL_2();
    }
}