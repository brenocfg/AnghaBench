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
struct snd_emux_voice {int ch; int /*<<< orphan*/  state; TYPE_1__* emu; } ;
struct snd_emux {struct snd_emux_voice* voices; } ;
struct snd_emu10k1 {struct snd_emux* synth; } ;
struct best_voice {size_t voice; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_voices; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SNDRV_EMUX_ST_OFF ; 
 int V_END ; 
 int /*<<< orphan*/  lookup_voices (struct snd_emux*,struct snd_emu10k1*,struct best_voice*,int) ; 

int
snd_emu10k1_synth_get_voice(struct snd_emu10k1 *hw)
{
	struct snd_emux *emu;
	struct snd_emux_voice *vp;
	struct best_voice best[V_END];
	int i;

	emu = hw->synth;

	lookup_voices(emu, hw, best, 1); /* no OFF voices */
	for (i = 0; i < V_END; i++) {
		if (best[i].voice >= 0) {
			int ch;
			vp = &emu->voices[best[i].voice];
			if ((ch = vp->ch) < 0) {
				/*
				dev_warn(emu->card->dev,
				       "synth_get_voice: ch < 0 (%d) ??", i);
				*/
				continue;
			}
			vp->emu->num_voices--;
			vp->ch = -1;
			vp->state = SNDRV_EMUX_ST_OFF;
			return ch;
		}
	}

	/* not found */
	return -ENOMEM;
}