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
struct TYPE_2__ {int dma_flags; struct snd_gf1_dma_block* dma_data_pcm_last; struct snd_gf1_dma_block* dma_data_pcm; struct snd_gf1_dma_block* dma_data_synth_last; struct snd_gf1_dma_block* dma_data_synth; } ;
struct snd_gus_card {int /*<<< orphan*/  dma_lock; TYPE_1__ gf1; } ;
struct snd_gf1_dma_block {scalar_t__ cmd; int /*<<< orphan*/  count; int /*<<< orphan*/  buf_addr; int /*<<< orphan*/  addr; struct snd_gf1_dma_block* next; scalar_t__ buffer; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNDRV_GF1_DMA_TRIGGER ; 
 int /*<<< orphan*/  kfree (struct snd_gf1_dma_block*) ; 
 struct snd_gf1_dma_block* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct snd_gf1_dma_block* snd_gf1_dma_next_block (struct snd_gus_card*) ; 
 int /*<<< orphan*/  snd_gf1_dma_program (struct snd_gus_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  snd_printdd (char*,long,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_gf1_dma_transfer_block(struct snd_gus_card * gus,
			       struct snd_gf1_dma_block * __block,
			       int atomic,
			       int synth)
{
	unsigned long flags;
	struct snd_gf1_dma_block *block;

	block = kmalloc(sizeof(*block), atomic ? GFP_ATOMIC : GFP_KERNEL);
	if (!block)
		return -ENOMEM;

	*block = *__block;
	block->next = NULL;

	snd_printdd("addr = 0x%x, buffer = 0x%lx, count = 0x%x, cmd = 0x%x\n",
		    block->addr, (long) block->buffer, block->count,
		    block->cmd);

	snd_printdd("gus->gf1.dma_data_pcm_last = 0x%lx\n",
		    (long)gus->gf1.dma_data_pcm_last);
	snd_printdd("gus->gf1.dma_data_pcm = 0x%lx\n",
		    (long)gus->gf1.dma_data_pcm);

	spin_lock_irqsave(&gus->dma_lock, flags);
	if (synth) {
		if (gus->gf1.dma_data_synth_last) {
			gus->gf1.dma_data_synth_last->next = block;
			gus->gf1.dma_data_synth_last = block;
		} else {
			gus->gf1.dma_data_synth = 
			gus->gf1.dma_data_synth_last = block;
		}
	} else {
		if (gus->gf1.dma_data_pcm_last) {
			gus->gf1.dma_data_pcm_last->next = block;
			gus->gf1.dma_data_pcm_last = block;
		} else {
			gus->gf1.dma_data_pcm = 
			gus->gf1.dma_data_pcm_last = block;
		}
	}
	if (!(gus->gf1.dma_flags & SNDRV_GF1_DMA_TRIGGER)) {
		gus->gf1.dma_flags |= SNDRV_GF1_DMA_TRIGGER;
		block = snd_gf1_dma_next_block(gus);
		spin_unlock_irqrestore(&gus->dma_lock, flags);
		if (block == NULL)
			return 0;
		snd_gf1_dma_program(gus, block->addr, block->buf_addr, block->count, (unsigned short) block->cmd);
		kfree(block);
		return 0;
	}
	spin_unlock_irqrestore(&gus->dma_lock, flags);
	return 0;
}