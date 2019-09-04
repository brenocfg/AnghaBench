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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct cmipci {int spdif_playback_avail; int /*<<< orphan*/  reg_lock; scalar_t__ spdif_playback_enabled; } ;
struct TYPE_2__ {int rate; } ;

/* Variables and functions */
 int CM_DBLSPDS ; 
 int CM_PLAYBACK_SPDF ; 
 int /*<<< orphan*/  CM_REG_CHFORMAT ; 
 int /*<<< orphan*/  CM_REG_FUNCTRL1 ; 
 int /*<<< orphan*/  CM_REG_MISC_CTRL ; 
 int CM_SPDF_AC97 ; 
 int CM_SPDIF48K ; 
 int save_mixer_state (struct cmipci*) ; 
 int /*<<< orphan*/  setup_ac3 (struct cmipci*,struct snd_pcm_substream*,int,int) ; 
 int /*<<< orphan*/  snd_cmipci_clear_bit (struct cmipci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_cmipci_set_bit (struct cmipci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setup_spdif_playback(struct cmipci *cm, struct snd_pcm_substream *subs, int up, int do_ac3)
{
	int rate, err;

	rate = subs->runtime->rate;

	if (up && do_ac3)
		if ((err = save_mixer_state(cm)) < 0)
			return err;

	spin_lock_irq(&cm->reg_lock);
	cm->spdif_playback_avail = up;
	if (up) {
		/* they are controlled via "IEC958 Output Switch" */
		/* snd_cmipci_set_bit(cm, CM_REG_LEGACY_CTRL, CM_ENSPDOUT); */
		/* snd_cmipci_set_bit(cm, CM_REG_FUNCTRL1, CM_SPDO2DAC); */
		if (cm->spdif_playback_enabled)
			snd_cmipci_set_bit(cm, CM_REG_FUNCTRL1, CM_PLAYBACK_SPDF);
		setup_ac3(cm, subs, do_ac3, rate);

		if (rate == 48000 || rate == 96000)
			snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_SPDIF48K | CM_SPDF_AC97);
		else
			snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_SPDIF48K | CM_SPDF_AC97);
		if (rate > 48000)
			snd_cmipci_set_bit(cm, CM_REG_CHFORMAT, CM_DBLSPDS);
		else
			snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_DBLSPDS);
	} else {
		/* they are controlled via "IEC958 Output Switch" */
		/* snd_cmipci_clear_bit(cm, CM_REG_LEGACY_CTRL, CM_ENSPDOUT); */
		/* snd_cmipci_clear_bit(cm, CM_REG_FUNCTRL1, CM_SPDO2DAC); */
		snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_DBLSPDS);
		snd_cmipci_clear_bit(cm, CM_REG_FUNCTRL1, CM_PLAYBACK_SPDF);
		setup_ac3(cm, subs, 0, 0);
	}
	spin_unlock_irq(&cm->reg_lock);
	return 0;
}