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
struct TYPE_2__ {int /*<<< orphan*/  dma_flags; int /*<<< orphan*/  (* dma_ack ) (struct snd_gus_card*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * dma_data_synth; int /*<<< orphan*/ * dma_data_pcm; int /*<<< orphan*/  dma_private_data; } ;
struct snd_gus_card {int /*<<< orphan*/  dma_lock; TYPE_1__ gf1; } ;
struct snd_gf1_dma_block {scalar_t__ cmd; int /*<<< orphan*/  count; int /*<<< orphan*/  buf_addr; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_GF1_DMA_TRIGGER ; 
 int /*<<< orphan*/  kfree (struct snd_gf1_dma_block*) ; 
 int /*<<< orphan*/  snd_gf1_dma_ack (struct snd_gus_card*) ; 
 struct snd_gf1_dma_block* snd_gf1_dma_next_block (struct snd_gus_card*) ; 
 int /*<<< orphan*/  snd_gf1_dma_program (struct snd_gus_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_gus_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_gf1_dma_interrupt(struct snd_gus_card * gus)
{
	struct snd_gf1_dma_block *block;

	snd_gf1_dma_ack(gus);
	if (gus->gf1.dma_ack)
		gus->gf1.dma_ack(gus, gus->gf1.dma_private_data);
	spin_lock(&gus->dma_lock);
	if (gus->gf1.dma_data_pcm == NULL &&
	    gus->gf1.dma_data_synth == NULL) {
	    	gus->gf1.dma_ack = NULL;
		gus->gf1.dma_flags &= ~SNDRV_GF1_DMA_TRIGGER;
		spin_unlock(&gus->dma_lock);
		return;
	}
	block = snd_gf1_dma_next_block(gus);
	spin_unlock(&gus->dma_lock);
	snd_gf1_dma_program(gus, block->addr, block->buf_addr, block->count, (unsigned short) block->cmd);
	kfree(block);
#if 0
	snd_printd(KERN_DEBUG "program dma (IRQ) - "
		   "addr = 0x%x, buffer = 0x%lx, count = 0x%x, cmd = 0x%x\n",
		   block->addr, block->buf_addr, block->count, block->cmd);
#endif
}