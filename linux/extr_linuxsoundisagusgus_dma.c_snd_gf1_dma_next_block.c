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
struct TYPE_2__ {int /*<<< orphan*/  dma_private_data; int /*<<< orphan*/  dma_ack; struct snd_gf1_dma_block* dma_data_synth; struct snd_gf1_dma_block* dma_data_synth_last; struct snd_gf1_dma_block* dma_data_pcm; struct snd_gf1_dma_block* dma_data_pcm_last; } ;
struct snd_gus_card {TYPE_1__ gf1; } ;
struct snd_gf1_dma_block {int /*<<< orphan*/  private_data; int /*<<< orphan*/  ack; struct snd_gf1_dma_block* next; } ;

/* Variables and functions */

__attribute__((used)) static struct snd_gf1_dma_block *snd_gf1_dma_next_block(struct snd_gus_card * gus)
{
	struct snd_gf1_dma_block *block;

	/* PCM block have bigger priority than synthesizer one */
	if (gus->gf1.dma_data_pcm) {
		block = gus->gf1.dma_data_pcm;
		if (gus->gf1.dma_data_pcm_last == block) {
			gus->gf1.dma_data_pcm =
			gus->gf1.dma_data_pcm_last = NULL;
		} else {
			gus->gf1.dma_data_pcm = block->next;
		}
	} else if (gus->gf1.dma_data_synth) {
		block = gus->gf1.dma_data_synth;
		if (gus->gf1.dma_data_synth_last == block) {
			gus->gf1.dma_data_synth =
			gus->gf1.dma_data_synth_last = NULL;
		} else {
			gus->gf1.dma_data_synth = block->next;
		}
	} else {
		block = NULL;
	}
	if (block) {
		gus->gf1.dma_ack = block->ack;
		gus->gf1.dma_private_data = block->private_data;
	}
	return block;
}