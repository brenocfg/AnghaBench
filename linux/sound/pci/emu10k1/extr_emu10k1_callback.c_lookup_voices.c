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
struct TYPE_2__ {int sample_mode; int loopstart; } ;
struct snd_emux_voice {int state; scalar_t__ ch; scalar_t__ time; TYPE_1__ reg; } ;
struct snd_emux {int max_voices; struct snd_emux_voice* voices; } ;
struct snd_emu10k1 {int dummy; } ;
struct best_voice {unsigned int time; int voice; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCCA_CURRADDR ; 
 int /*<<< orphan*/  CVCF_CURRENTVOL ; 
 int SNDRV_EMUX_ST_OFF ; 
 int SNDRV_EMUX_ST_ON ; 
 int SNDRV_EMUX_ST_PENDING ; 
 int SNDRV_EMUX_ST_RELEASED ; 
 int SNDRV_EMUX_ST_STANDBY ; 
 int SNDRV_SFNT_SAMPLE_SINGLESHOT ; 
 int V_END ; 
 int V_FREE ; 
 int V_OFF ; 
 int V_PLAYING ; 
 int V_RELEASED ; 
 int snd_emu10k1_ptr_read (struct snd_emu10k1*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
lookup_voices(struct snd_emux *emu, struct snd_emu10k1 *hw,
	      struct best_voice *best, int active_only)
{
	struct snd_emux_voice *vp;
	struct best_voice *bp;
	int  i;

	for (i = 0; i < V_END; i++) {
		best[i].time = (unsigned int)-1; /* XXX MAX_?INT really */
		best[i].voice = -1;
	}

	/*
	 * Go through them all and get a best one to use.
	 * NOTE: could also look at volume and pick the quietest one.
	 */
	for (i = 0; i < emu->max_voices; i++) {
		int state, val;

		vp = &emu->voices[i];
		state = vp->state;
		if (state == SNDRV_EMUX_ST_OFF) {
			if (vp->ch < 0) {
				if (active_only)
					continue;
				bp = best + V_FREE;
			} else
				bp = best + V_OFF;
		}
		else if (state == SNDRV_EMUX_ST_RELEASED ||
			 state == SNDRV_EMUX_ST_PENDING) {
			bp = best + V_RELEASED;
#if 1
			val = snd_emu10k1_ptr_read(hw, CVCF_CURRENTVOL, vp->ch);
			if (! val)
				bp = best + V_OFF;
#endif
		}
		else if (state == SNDRV_EMUX_ST_STANDBY)
			continue;
		else if (state & SNDRV_EMUX_ST_ON)
			bp = best + V_PLAYING;
		else
			continue;

		/* check if sample is finished playing (non-looping only) */
		if (bp != best + V_OFF && bp != best + V_FREE &&
		    (vp->reg.sample_mode & SNDRV_SFNT_SAMPLE_SINGLESHOT)) {
			val = snd_emu10k1_ptr_read(hw, CCCA_CURRADDR, vp->ch);
			if (val >= vp->reg.loopstart)
				bp = best + V_OFF;
		}

		if (vp->time < bp->time) {
			bp->time = vp->time;
			bp->voice = i;
		}
	}
}