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
struct snd_midi_channel {int midi_pitchbend; int gm_rpn_pitch_bend_range; int gm_rpn_coarse_tuning; int gm_rpn_fine_tuning; struct snd_emux_effect_table* private; } ;
struct TYPE_3__ {scalar_t__ fixkey; int root; int scaleTuning; int tune; scalar_t__ rate_offset; } ;
struct snd_emux_voice {int note; int apitch; TYPE_2__* emu; TYPE_1__ reg; struct snd_midi_channel* chan; } ;
struct snd_emux_effect_table {scalar_t__* val; scalar_t__* flag; } ;
struct TYPE_4__ {scalar_t__ pitch_shift; } ;

/* Variables and functions */
 size_t EMUX_FX_INIT_PITCH ; 
 int /*<<< orphan*/  LIMITVALUE (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
calc_pitch(struct snd_emux_voice *vp)
{
	struct snd_midi_channel *chan = vp->chan;
	int offset;

	/* calculate offset */
	if (vp->reg.fixkey >= 0) {
		offset = (vp->reg.fixkey - vp->reg.root) * 4096 / 12;
	} else {
		offset = (vp->note - vp->reg.root) * 4096 / 12;
	}
	offset = (offset * vp->reg.scaleTuning) / 100;
	offset += vp->reg.tune * 4096 / 1200;
	if (chan->midi_pitchbend != 0) {
		/* (128 * 8192: 1 semitone) ==> (4096: 12 semitones) */
		offset += chan->midi_pitchbend * chan->gm_rpn_pitch_bend_range / 3072;
	}

	/* tuning via RPN:
	 *   coarse = -8192 to 8192 (100 cent per 128)
	 *   fine = -8192 to 8192 (max=100cent)
	 */
	/* 4096 = 1200 cents in emu8000 parameter */
	offset += chan->gm_rpn_coarse_tuning * 4096 / (12 * 128);
	offset += chan->gm_rpn_fine_tuning / 24;

#ifdef SNDRV_EMUX_USE_RAW_EFFECT
	/* add initial pitch correction */
	if (chan->private) {
		struct snd_emux_effect_table *fx = chan->private;
		if (fx->flag[EMUX_FX_INIT_PITCH])
			offset += fx->val[EMUX_FX_INIT_PITCH];
	}
#endif

	/* 0xe000: root pitch */
	offset += 0xe000 + vp->reg.rate_offset;
	offset += vp->emu->pitch_shift;
	LIMITVALUE(offset, 0, 0xffff);
	if (offset == vp->apitch)
		return 0; /* unchanged */
	vp->apitch = offset;
	return 1; /* value changed */
}