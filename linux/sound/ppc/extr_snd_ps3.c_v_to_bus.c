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
struct snd_ps3_card_info {int* dma_start_bus_addr; void** dma_start_vaddr; } ;
typedef  int dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static dma_addr_t v_to_bus(struct snd_ps3_card_info *card, void *paddr, int ch)
{
	return card->dma_start_bus_addr[ch] +
		(paddr - card->dma_start_vaddr[ch]);
}