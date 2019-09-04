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
struct snd_emu10k1 {int /*<<< orphan*/ ** page_ptr_table; scalar_t__* page_addr_table; scalar_t__ iommu_workaround; int /*<<< orphan*/  pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  type; } ;
struct snd_dma_buffer {int bytes; scalar_t__ addr; int /*<<< orphan*/ * area; TYPE_1__ dev; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  snd_dma_free_pages (struct snd_dma_buffer*) ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __synth_free_pages(struct snd_emu10k1 *emu, int first_page,
			       int last_page)
{
	struct snd_dma_buffer dmab;
	int page;

	dmab.dev.type = SNDRV_DMA_TYPE_DEV;
	dmab.dev.dev = snd_dma_pci_data(emu->pci);

	for (page = first_page; page <= last_page; page++) {
		if (emu->page_ptr_table[page] == NULL)
			continue;
		dmab.area = emu->page_ptr_table[page];
		dmab.addr = emu->page_addr_table[page];

		/*
		 * please keep me in sync with logic in
		 * snd_emu10k1_alloc_pages_maybe_wider()
		 */
		dmab.bytes = PAGE_SIZE;
		if (emu->iommu_workaround)
			dmab.bytes *= 2;

		snd_dma_free_pages(&dmab);
		emu->page_addr_table[page] = 0;
		emu->page_ptr_table[page] = NULL;
	}
}