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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int pcm_rcntrl_reg; } ;
struct snd_gus_card {int /*<<< orphan*/  reg_lock; TYPE_1__ gf1; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_GF1_GB_REC_DMA_CONTROL ; 
 int SNDRV_PCM_TRIGGER_START ; 
 int SNDRV_PCM_TRIGGER_STOP ; 
 int /*<<< orphan*/  snd_gf1_look8 (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_write8 (struct snd_gus_card*,int /*<<< orphan*/ ,int) ; 
 struct snd_gus_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_gf1_pcm_capture_trigger(struct snd_pcm_substream *substream,
				       int cmd)
{
	struct snd_gus_card *gus = snd_pcm_substream_chip(substream);
	int val;
	
	if (cmd == SNDRV_PCM_TRIGGER_START) {
		val = gus->gf1.pcm_rcntrl_reg;
	} else if (cmd == SNDRV_PCM_TRIGGER_STOP) {
		val = 0;
	} else {
		return -EINVAL;
	}

	spin_lock(&gus->reg_lock);
	snd_gf1_write8(gus, SNDRV_GF1_GB_REC_DMA_CONTROL, val);
	snd_gf1_look8(gus, SNDRV_GF1_GB_REC_DMA_CONTROL);
	spin_unlock(&gus->reg_lock);
	return 0;
}