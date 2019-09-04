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
struct snd_opl4 {int dummy; } ;
struct snd_midi_channel {int gm_rpn_fine_tuning; int midi_pitchbend; int gm_rpn_pitch_bend_range; scalar_t__ gm_rpn_coarse_tuning; scalar_t__ drum_channel; } ;
struct opl4_voice {int note; int reg_f_number; scalar_t__ number; TYPE_1__* sound; struct snd_midi_channel* chan; } ;
struct TYPE_2__ {int key_scaling; scalar_t__ pitch_offset; } ;

/* Variables and functions */
 int OPL4_F_NUMBER_HIGH_MASK ; 
 int OPL4_F_NUMBER_LOW_MASK ; 
 scalar_t__ OPL4_REG_F_NUMBER ; 
 scalar_t__ OPL4_REG_OCTAVE ; 
 int OPL4_TONE_NUMBER_BIT8 ; 
 int* snd_opl4_pitch_map ; 
 int /*<<< orphan*/  snd_opl4_write (struct snd_opl4*,scalar_t__,int) ; 

__attribute__((used)) static void snd_opl4_update_pitch(struct snd_opl4 *opl4,
				  struct opl4_voice *voice)
{
	struct snd_midi_channel *chan = voice->chan;
	int note, pitch, octave;

	note = chan->drum_channel ? 60 : voice->note;
	/*
	 * pitch is in 100/128 cents, so 0x80 is one semitone and
	 * 0x600 is one octave.
	 */
	pitch = ((note - 60) << 7) * voice->sound->key_scaling / 100 + (60 << 7);
	pitch += voice->sound->pitch_offset;
	if (!chan->drum_channel)
		pitch += chan->gm_rpn_coarse_tuning;
	pitch += chan->gm_rpn_fine_tuning >> 7;
	pitch += chan->midi_pitchbend * chan->gm_rpn_pitch_bend_range / 0x2000;
	if (pitch < 0)
		pitch = 0;
	else if (pitch >= 0x6000)
		pitch = 0x5fff;
	octave = pitch / 0x600 - 8;
	pitch = snd_opl4_pitch_map[pitch % 0x600];

	snd_opl4_write(opl4, OPL4_REG_OCTAVE + voice->number,
		       (octave << 4) | ((pitch >> 7) & OPL4_F_NUMBER_HIGH_MASK));
	voice->reg_f_number = (voice->reg_f_number & OPL4_TONE_NUMBER_BIT8)
		| ((pitch << 1) & OPL4_F_NUMBER_LOW_MASK);
	snd_opl4_write(opl4, OPL4_REG_F_NUMBER + voice->number, voice->reg_f_number);
}