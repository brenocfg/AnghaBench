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
 float PITCH_STANDARD_A ; 
 float pow (double,int) ; 

float compute_freq_for_midi_note(uint8_t note) {
    // https://en.wikipedia.org/wiki/MIDI_tuning_standard
    return pow(2.0, (note - 69) / 12.0) * PITCH_STANDARD_A;
}