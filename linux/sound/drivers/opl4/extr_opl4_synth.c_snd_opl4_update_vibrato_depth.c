#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_opl4 {int dummy; } ;
struct opl4_voice {int reg_lfo_vibrato; scalar_t__ number; TYPE_2__* sound; TYPE_1__* chan; } ;
struct TYPE_4__ {int vibrato; } ;
struct TYPE_3__ {int* control; scalar_t__ drum_channel; } ;

/* Variables and functions */
 size_t MIDI_CTL_VIBRATO_DEPTH ; 
 scalar_t__ OPL4_REG_LFO_VIBRATO ; 
 int OPL4_VIBRATO_DEPTH_MASK ; 
 int /*<<< orphan*/  snd_opl4_write (struct snd_opl4*,scalar_t__,int) ; 

__attribute__((used)) static void snd_opl4_update_vibrato_depth(struct snd_opl4 *opl4,
					  struct opl4_voice *voice)
{
	int depth;

	if (voice->chan->drum_channel)
		return;
	depth = (7 - voice->sound->vibrato)
		* (voice->chan->control[MIDI_CTL_VIBRATO_DEPTH] & 0x7f);
	depth = (depth >> 7) + voice->sound->vibrato;
	voice->reg_lfo_vibrato &= ~OPL4_VIBRATO_DEPTH_MASK;
	voice->reg_lfo_vibrato |= depth & OPL4_VIBRATO_DEPTH_MASK;
	snd_opl4_write(opl4, OPL4_REG_LFO_VIBRATO + voice->number,
		       voice->reg_lfo_vibrato);
}