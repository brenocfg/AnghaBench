#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_runtime {int channels; } ;
struct snd_gus_voice {int /*<<< orphan*/  number; struct gus_pcm_private* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  enh_mode; } ;
struct snd_gus_card {int /*<<< orphan*/  reg_lock; TYPE_1__ gf1; } ;
struct gus_pcm_private {int bpos; int blocks; int memory; int block_size; unsigned int dma_size; unsigned int voices; TYPE_3__* substream; TYPE_2__** pvoices; int /*<<< orphan*/  final_volume; struct snd_gus_card* gus; } ;
struct TYPE_6__ {struct snd_pcm_runtime* runtime; } ;
struct TYPE_5__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_GF1_VA_END ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_ADDRESS_CONTROL ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_VOLUME_CONTROL ; 
 int /*<<< orphan*/  snd_gf1_delay (struct snd_gus_card*) ; 
 int snd_gf1_read8 (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_select_voice (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_smart_stop_voice (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_write8 (struct snd_gus_card*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  snd_gf1_write_addr (struct snd_gus_card*,int /*<<< orphan*/ ,unsigned int,unsigned char) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (TYPE_3__*) ; 
 int /*<<< orphan*/  snd_printd (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_gf1_pcm_interrupt_wave(struct snd_gus_card * gus,
				       struct snd_gus_voice *pvoice)
{
	struct gus_pcm_private * pcmp;
	struct snd_pcm_runtime *runtime;
	unsigned char voice_ctrl, ramp_ctrl;
	unsigned int idx;
	unsigned int end, step;

	if (!pvoice->private_data) {
		snd_printd("snd_gf1_pcm: unknown wave irq?\n");
		snd_gf1_smart_stop_voice(gus, pvoice->number);
		return;
	}
	pcmp = pvoice->private_data;
	if (pcmp == NULL) {
		snd_printd("snd_gf1_pcm: unknown wave irq?\n");
		snd_gf1_smart_stop_voice(gus, pvoice->number);
		return;
	}		
	gus = pcmp->gus;
	runtime = pcmp->substream->runtime;

	spin_lock(&gus->reg_lock);
	snd_gf1_select_voice(gus, pvoice->number);
	voice_ctrl = snd_gf1_read8(gus, SNDRV_GF1_VB_ADDRESS_CONTROL) & ~0x8b;
	ramp_ctrl = (snd_gf1_read8(gus, SNDRV_GF1_VB_VOLUME_CONTROL) & ~0xa4) | 0x03;
#if 0
	snd_gf1_select_voice(gus, pvoice->number);
	printk(KERN_DEBUG "position = 0x%x\n",
	       (snd_gf1_read_addr(gus, SNDRV_GF1_VA_CURRENT, voice_ctrl & 4) >> 4));
	snd_gf1_select_voice(gus, pcmp->pvoices[1]->number);
	printk(KERN_DEBUG "position = 0x%x\n",
	       (snd_gf1_read_addr(gus, SNDRV_GF1_VA_CURRENT, voice_ctrl & 4) >> 4));
	snd_gf1_select_voice(gus, pvoice->number);
#endif
	pcmp->bpos++;
	pcmp->bpos %= pcmp->blocks;
	if (pcmp->bpos + 1 >= pcmp->blocks) {	/* last block? */
		voice_ctrl |= 0x08;	/* enable loop */
	} else {
		ramp_ctrl |= 0x04;	/* enable rollover */
	}
	end = pcmp->memory + (((pcmp->bpos + 1) * pcmp->block_size) / runtime->channels);
	end -= voice_ctrl & 4 ? 2 : 1;
	step = pcmp->dma_size / runtime->channels;
	voice_ctrl |= 0x20;
	if (!pcmp->final_volume) {
		ramp_ctrl |= 0x20;
		ramp_ctrl &= ~0x03;
	}
	for (idx = 0; idx < pcmp->voices; idx++, end += step) {
		snd_gf1_select_voice(gus, pcmp->pvoices[idx]->number);
		snd_gf1_write_addr(gus, SNDRV_GF1_VA_END, end << 4, voice_ctrl & 4);
		snd_gf1_write8(gus, SNDRV_GF1_VB_ADDRESS_CONTROL, voice_ctrl);
		snd_gf1_write8(gus, SNDRV_GF1_VB_VOLUME_CONTROL, ramp_ctrl);
		voice_ctrl &= ~0x20;
	}
	if (!gus->gf1.enh_mode) {
		snd_gf1_delay(gus);
		voice_ctrl |= 0x20;
		for (idx = 0; idx < pcmp->voices; idx++) {
			snd_gf1_select_voice(gus, pcmp->pvoices[idx]->number);
			snd_gf1_write8(gus, SNDRV_GF1_VB_ADDRESS_CONTROL, voice_ctrl);
			snd_gf1_write8(gus, SNDRV_GF1_VB_VOLUME_CONTROL, ramp_ctrl);
			voice_ctrl &= ~0x20;
		}
	}
	spin_unlock(&gus->reg_lock);

	snd_pcm_period_elapsed(pcmp->substream);
#if 0
	if ((runtime->flags & SNDRV_PCM_FLG_MMAP) &&
	    *runtime->state == SNDRV_PCM_STATE_RUNNING) {
		end = pcmp->bpos * pcmp->block_size;
		if (runtime->channels > 1) {
			snd_gf1_pcm_block_change(pcmp->substream, end, pcmp->memory + (end / 2), pcmp->block_size / 2);
			snd_gf1_pcm_block_change(pcmp->substream, end + (pcmp->block_size / 2), pcmp->memory + (pcmp->dma_size / 2) + (end / 2), pcmp->block_size / 2);
		} else {
			snd_gf1_pcm_block_change(pcmp->substream, end, pcmp->memory + end, pcmp->block_size);
		}
	}
#endif
}