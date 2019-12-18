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
 int /*<<< orphan*/  GPTD6 ; 
 int /*<<< orphan*/  GPTD7 ; 
 int /*<<< orphan*/  GPTD8 ; 
 int /*<<< orphan*/  audio_init () ; 
 int /*<<< orphan*/  audio_initialized ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 scalar_t__* frequencies ; 
 scalar_t__ frequency ; 
 scalar_t__ frequency_alt ; 
 int /*<<< orphan*/  gptStopTimer (int /*<<< orphan*/ *) ; 
 int playing_note ; 
 int playing_notes ; 
 scalar_t__ voices ; 
 scalar_t__ volume ; 
 scalar_t__* volumes ; 

void stop_all_notes() {
    dprintf("audio stop all notes");

    if (!audio_initialized) {
        audio_init();
    }
    voices = 0;

    gptStopTimer(&GPTD6);
    gptStopTimer(&GPTD7);
    gptStopTimer(&GPTD8);

    playing_notes = false;
    playing_note  = false;
    frequency     = 0;
    frequency_alt = 0;
    volume        = 0;

    for (uint8_t i = 0; i < 8; i++) {
        frequencies[i] = 0;
        volumes[i]     = 0;
    }
}