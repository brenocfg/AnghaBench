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
struct snd_opl3 {int /*<<< orphan*/  drum_reg; int /*<<< orphan*/  (* command ) (struct snd_opl3*,int,int /*<<< orphan*/ ) ;} ;
struct snd_midi_channel {int* control; } ;

/* Variables and functions */
#define  MIDI_CTL_E2_TREMOLO_DEPTH 130 
#define  MIDI_CTL_MSB_MODWHEEL 129 
#define  MIDI_CTL_PITCHBEND 128 
 int OPL3_LEFT ; 
 int OPL3_REG_PERCUSSION ; 
 int /*<<< orphan*/  OPL3_TREMOLO_DEPTH ; 
 int /*<<< orphan*/  OPL3_VIBRATO_DEPTH ; 
 int /*<<< orphan*/  snd_opl3_pitch_ctrl (struct snd_opl3*,struct snd_midi_channel*) ; 
 int /*<<< orphan*/  stub1 (struct snd_opl3*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct snd_opl3*,int,int /*<<< orphan*/ ) ; 

void snd_opl3_control(void *p, int type, struct snd_midi_channel *chan)
{
  	struct snd_opl3 *opl3;

	opl3 = p;
#ifdef DEBUG_MIDI
	snd_printk(KERN_DEBUG "Controller, TYPE = %i, ch#: %i, inst#: %i\n",
		   type, chan->number, chan->midi_program);
#endif

	switch (type) {
	case MIDI_CTL_MSB_MODWHEEL:
		if (chan->control[MIDI_CTL_MSB_MODWHEEL] > 63)
			opl3->drum_reg |= OPL3_VIBRATO_DEPTH;
		else 
			opl3->drum_reg &= ~OPL3_VIBRATO_DEPTH;
		opl3->command(opl3, OPL3_LEFT | OPL3_REG_PERCUSSION,
				 opl3->drum_reg);
		break;
	case MIDI_CTL_E2_TREMOLO_DEPTH:
		if (chan->control[MIDI_CTL_E2_TREMOLO_DEPTH] > 63)
			opl3->drum_reg |= OPL3_TREMOLO_DEPTH;
		else 
			opl3->drum_reg &= ~OPL3_TREMOLO_DEPTH;
		opl3->command(opl3, OPL3_LEFT | OPL3_REG_PERCUSSION,
				 opl3->drum_reg);
		break;
	case MIDI_CTL_PITCHBEND:
		snd_opl3_pitch_ctrl(opl3, chan);
		break;
	}
}