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
struct snd_gus_voice {int /*<<< orphan*/  number; struct gus_pcm_private* private_data; } ;
struct TYPE_2__ {unsigned short pcm_volume_level_left; unsigned short pcm_volume_level_right; } ;
struct snd_gus_card {int /*<<< orphan*/  reg_lock; TYPE_1__ gf1; } ;
struct gus_pcm_private {int flags; int final_volume; int /*<<< orphan*/ * substream; struct snd_gus_voice** pvoices; } ;

/* Variables and functions */
 int SNDRV_GF1_PCM_PFLG_ACTIVE ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_VOLUME_CONTROL ; 
 int /*<<< orphan*/  SNDRV_GF1_VW_VOLUME ; 
 int /*<<< orphan*/  snd_gf1_ctrl_stop (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_select_voice (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_write16 (struct snd_gus_card*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_gf1_pcm_interrupt_volume(struct snd_gus_card * gus,
					 struct snd_gus_voice * pvoice)
{
	unsigned short vol;
	int cvoice;
	struct gus_pcm_private *pcmp = pvoice->private_data;

	/* stop ramp, but leave rollover bit untouched */
	spin_lock(&gus->reg_lock);
	snd_gf1_select_voice(gus, pvoice->number);
	snd_gf1_ctrl_stop(gus, SNDRV_GF1_VB_VOLUME_CONTROL);
	spin_unlock(&gus->reg_lock);
	if (pcmp == NULL)
		return;
	/* are we active? */
	if (!(pcmp->flags & SNDRV_GF1_PCM_PFLG_ACTIVE))
		return;
	/* load real volume - better precision */
	cvoice = pcmp->pvoices[0] == pvoice ? 0 : 1;
	if (pcmp->substream == NULL)
		return;
	vol = !cvoice ? gus->gf1.pcm_volume_level_left : gus->gf1.pcm_volume_level_right;
	spin_lock(&gus->reg_lock);
	snd_gf1_select_voice(gus, pvoice->number);
	snd_gf1_write16(gus, SNDRV_GF1_VW_VOLUME, vol);
	pcmp->final_volume = 1;
	spin_unlock(&gus->reg_lock);
}