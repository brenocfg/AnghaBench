#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_ps3_card_info {scalar_t__* dma_last_transfer_vaddr; scalar_t__* dma_next_transfer_vaddr; scalar_t__* dma_start_vaddr; int dma_buffer_size; } ;
typedef  enum snd_ps3_ch { ____Placeholder_snd_ps3_ch } snd_ps3_ch ;

/* Variables and functions */

__attribute__((used)) static void snd_ps3_bump_buffer(struct snd_ps3_card_info *card,
				enum snd_ps3_ch ch, size_t byte_count,
				int stage)
{
	if (!stage)
		card->dma_last_transfer_vaddr[ch] =
			card->dma_next_transfer_vaddr[ch];
	card->dma_next_transfer_vaddr[ch] += byte_count;
	if ((card->dma_start_vaddr[ch] + (card->dma_buffer_size / 2)) <=
	    card->dma_next_transfer_vaddr[ch]) {
		card->dma_next_transfer_vaddr[ch] = card->dma_start_vaddr[ch];
	}
}