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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {scalar_t__ enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE_AUDIO_COUNTER_1_ISR ; 
 int /*<<< orphan*/  DISABLE_AUDIO_COUNTER_3_ISR ; 
 int /*<<< orphan*/  ENABLE_AUDIO_COUNTER_1_ISR ; 
 int /*<<< orphan*/  ENABLE_AUDIO_COUNTER_1_OUTPUT ; 
 int /*<<< orphan*/  ENABLE_AUDIO_COUNTER_3_ISR ; 
 int /*<<< orphan*/  ENABLE_AUDIO_COUNTER_3_OUTPUT ; 
 TYPE_1__ audio_config ; 
 int /*<<< orphan*/  audio_init () ; 
 int /*<<< orphan*/  audio_initialized ; 
 size_t current_note ; 
 int note_frequency ; 
 int note_length ; 
 scalar_t__ note_position ; 
 scalar_t__ note_tempo ; 
 int /*<<< orphan*/  notes_count ; 
 int*** notes_pointer ; 
 int notes_repeat ; 
 scalar_t__ place ; 
 scalar_t__ playing_note ; 
 int playing_notes ; 
 int /*<<< orphan*/  stop_all_notes () ; 

void play_notes(float (*np)[][2], uint16_t n_count, bool n_repeat) {
    if (!audio_initialized) {
        audio_init();
    }

    if (audio_config.enable) {
#ifdef CPIN_AUDIO
        DISABLE_AUDIO_COUNTER_3_ISR;
#endif
#ifdef BPIN_AUDIO
        DISABLE_AUDIO_COUNTER_1_ISR;
#endif

        // Cancel note if a note is playing
        if (playing_note) stop_all_notes();

        playing_notes = true;

        notes_pointer = np;
        notes_count   = n_count;
        notes_repeat  = n_repeat;

        place        = 0;
        current_note = 0;

        note_frequency = (*notes_pointer)[current_note][0];
        note_length    = ((*notes_pointer)[current_note][1] / 4) * (((float)note_tempo) / 100);
        note_position  = 0;

#ifdef CPIN_AUDIO
        ENABLE_AUDIO_COUNTER_3_ISR;
        ENABLE_AUDIO_COUNTER_3_OUTPUT;
#endif
#ifdef BPIN_AUDIO
#    ifndef CPIN_AUDIO
        ENABLE_AUDIO_COUNTER_1_ISR;
        ENABLE_AUDIO_COUNTER_1_OUTPUT;
#    endif
#endif
    }
}