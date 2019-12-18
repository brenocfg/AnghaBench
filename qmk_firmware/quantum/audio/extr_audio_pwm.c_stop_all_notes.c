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

/* Variables and functions */
 int /*<<< orphan*/  DISABLE_AUDIO_COUNTER_3_ISR ; 
 int /*<<< orphan*/  DISABLE_AUDIO_COUNTER_3_OUTPUT ; 
 int /*<<< orphan*/  audio_init () ; 
 int /*<<< orphan*/  audio_initialized ; 
 scalar_t__* frequencies ; 
 scalar_t__ frequency ; 
 int playing_note ; 
 int playing_notes ; 
 scalar_t__ voices ; 
 scalar_t__ volume ; 
 scalar_t__* volumes ; 

void stop_all_notes() {
    if (!audio_initialized) {
        audio_init();
    }
    voices = 0;
#ifdef PWM_AUDIO
    DISABLE_AUDIO_COUNTER_3_ISR;
#else
    DISABLE_AUDIO_COUNTER_3_ISR;
    DISABLE_AUDIO_COUNTER_3_OUTPUT;
#endif

    playing_notes = false;
    playing_note  = false;
    frequency     = 0;
    volume        = 0;

    for (uint8_t i = 0; i < 8; i++) {
        frequencies[i] = 0;
        volumes[i]     = 0;
    }
}