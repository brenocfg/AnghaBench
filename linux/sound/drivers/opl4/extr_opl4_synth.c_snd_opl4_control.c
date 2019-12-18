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
struct snd_opl4 {int dummy; } ;
struct snd_midi_channel {int /*<<< orphan*/ * control; } ;

/* Variables and functions */
#define  MIDI_CTL_E1_REVERB_DEPTH 136 
#define  MIDI_CTL_MSB_EXPRESSION 135 
#define  MIDI_CTL_MSB_MAIN_VOLUME 134 
#define  MIDI_CTL_MSB_MODWHEEL 133 
#define  MIDI_CTL_MSB_PAN 132 
#define  MIDI_CTL_PITCHBEND 131 
#define  MIDI_CTL_VIBRATO_DELAY 130 
#define  MIDI_CTL_VIBRATO_DEPTH 129 
#define  MIDI_CTL_VIBRATO_RATE 128 
 int /*<<< orphan*/  snd_opl4_do_for_channel (struct snd_opl4*,struct snd_midi_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_opl4_update_pan ; 
 int /*<<< orphan*/  snd_opl4_update_pitch ; 
 int /*<<< orphan*/  snd_opl4_update_vibrato_depth ; 
 int /*<<< orphan*/  snd_opl4_update_volume ; 

void snd_opl4_control(void *private_data, int type, struct snd_midi_channel *chan)
{
	struct snd_opl4 *opl4 = private_data;

	switch (type) {
	case MIDI_CTL_MSB_MODWHEEL:
		chan->control[MIDI_CTL_VIBRATO_DEPTH] = chan->control[MIDI_CTL_MSB_MODWHEEL];
		snd_opl4_do_for_channel(opl4, chan, snd_opl4_update_vibrato_depth);
		break;
	case MIDI_CTL_MSB_MAIN_VOLUME:
		snd_opl4_do_for_channel(opl4, chan, snd_opl4_update_volume);
		break;
	case MIDI_CTL_MSB_PAN:
		snd_opl4_do_for_channel(opl4, chan, snd_opl4_update_pan);
		break;
	case MIDI_CTL_MSB_EXPRESSION:
		snd_opl4_do_for_channel(opl4, chan, snd_opl4_update_volume);
		break;
	case MIDI_CTL_VIBRATO_RATE:
		/* not yet supported */
		break;
	case MIDI_CTL_VIBRATO_DEPTH:
		snd_opl4_do_for_channel(opl4, chan, snd_opl4_update_vibrato_depth);
		break;
	case MIDI_CTL_VIBRATO_DELAY:
		/* not yet supported */
		break;
	case MIDI_CTL_E1_REVERB_DEPTH:
		/*
		 * Each OPL4 voice has a bit called "Pseudo-Reverb", but
		 * IMHO _not_ using it enhances the listening experience.
		 */
		break;
	case MIDI_CTL_PITCHBEND:
		snd_opl4_do_for_channel(opl4, chan, snd_opl4_update_pitch);
		break;
	}
}