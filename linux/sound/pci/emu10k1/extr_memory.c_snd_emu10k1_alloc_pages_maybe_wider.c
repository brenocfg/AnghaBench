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
struct snd_emu10k1 {int /*<<< orphan*/  pci; scalar_t__ iommu_workaround; } ;
struct snd_dma_buffer {int dummy; } ;

/* Variables and functions */
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int snd_dma_alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,struct snd_dma_buffer*) ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 

int snd_emu10k1_alloc_pages_maybe_wider(struct snd_emu10k1 *emu, size_t size,
					struct snd_dma_buffer *dmab)
{
	if (emu->iommu_workaround) {
		size_t npages = (size + PAGE_SIZE - 1) / PAGE_SIZE;
		size_t size_real = npages * PAGE_SIZE;

		/*
		 * The device has been observed to accesses up to 256 extra
		 * bytes, but use 1k to be safe.
		 */
		if (size_real < size + 1024)
			size += PAGE_SIZE;
	}

	return snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV,
				   snd_dma_pci_data(emu->pci), size, dmab);
}