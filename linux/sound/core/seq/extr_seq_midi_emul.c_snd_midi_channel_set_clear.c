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
struct snd_midi_channel_set {int gs_master_volume; int max_channels; struct snd_midi_channel* channels; int /*<<< orphan*/  midi_mode; } ;
struct snd_midi_channel {int gm_rpn_pitch_bend_range; int drum_channel; scalar_t__ gm_rpn_coarse_tuning; scalar_t__ gm_rpn_fine_tuning; scalar_t__ midi_pitchbend; scalar_t__ midi_program; scalar_t__ midi_pressure; scalar_t__ midi_aftertouch; int /*<<< orphan*/  note; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_MIDI_MODE_GM ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_midi_reset_controllers (struct snd_midi_channel*) ; 

void
snd_midi_channel_set_clear(struct snd_midi_channel_set *chset)
{
	int i;

	chset->midi_mode = SNDRV_MIDI_MODE_GM;
	chset->gs_master_volume = 127;

	for (i = 0; i < chset->max_channels; i++) {
		struct snd_midi_channel *chan = chset->channels + i;
		memset(chan->note, 0, sizeof(chan->note));

		chan->midi_aftertouch = 0;
		chan->midi_pressure = 0;
		chan->midi_program = 0;
		chan->midi_pitchbend = 0;
		snd_midi_reset_controllers(chan);
		chan->gm_rpn_pitch_bend_range = 256; /* 2 semitones */
		chan->gm_rpn_fine_tuning = 0;
		chan->gm_rpn_coarse_tuning = 0;

		if (i == 9)
			chan->drum_channel = 1;
		else
			chan->drum_channel = 0;
	}
}