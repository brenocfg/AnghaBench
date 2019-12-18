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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__* SCALE ; 
 int /*<<< orphan*/  compute_freq_for_midi_note (scalar_t__) ; 
 scalar_t__ last_muse_note ; 
 size_t muse_clock_pulse () ; 
 int muse_counter ; 
 scalar_t__ muse_mode ; 
 scalar_t__ muse_offset ; 
 int muse_tempo ; 
 int /*<<< orphan*/  play_note (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stop_note (int /*<<< orphan*/ ) ; 

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}