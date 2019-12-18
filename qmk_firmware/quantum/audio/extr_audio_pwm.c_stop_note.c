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
 int /*<<< orphan*/  DISABLE_AUDIO_COUNTER_3_ISR ; 
 int /*<<< orphan*/  DISABLE_AUDIO_COUNTER_3_OUTPUT ; 
 float SAMPLE_RATE ; 
 int /*<<< orphan*/  audio_init () ; 
 int /*<<< orphan*/  audio_initialized ; 
 float* frequencies ; 
 scalar_t__ frequency ; 
 int playing_note ; 
 scalar_t__ voice_place ; 
 scalar_t__ voices ; 
 scalar_t__ volume ; 
 scalar_t__* volumes ; 

void stop_note(float freq) {
    if (playing_note) {
        if (!audio_initialized) {
            audio_init();
        }
#ifdef PWM_AUDIO
        freq = freq / SAMPLE_RATE;
#endif
        for (int i = 7; i >= 0; i--) {
            if (frequencies[i] == freq) {
                frequencies[i] = 0;
                volumes[i]     = 0;
                for (int j = i; (j < 7); j++) {
                    frequencies[j]     = frequencies[j + 1];
                    frequencies[j + 1] = 0;
                    volumes[j]         = volumes[j + 1];
                    volumes[j + 1]     = 0;
                }
                break;
            }
        }
        voices--;
        if (voices < 0) voices = 0;
        if (voice_place >= voices) {
            voice_place = 0;
        }
        if (voices == 0) {
#ifdef PWM_AUDIO
            DISABLE_AUDIO_COUNTER_3_ISR;
#else
            DISABLE_AUDIO_COUNTER_3_ISR;
            DISABLE_AUDIO_COUNTER_3_OUTPUT;
#endif
            frequency    = 0;
            volume       = 0;
            playing_note = false;
        }
    }
}