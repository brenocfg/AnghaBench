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
struct page {int dummy; } ;
struct hmm_range {scalar_t__ end; scalar_t__ start; int* pfns; int* flags; int* values; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int DMA_BIDIRECTIONAL ; 
 int DMA_TO_DEVICE ; 
 long EINVAL ; 
 size_t HMM_PFN_NONE ; 
 size_t HMM_PFN_WRITE ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct page* hmm_device_entry_to_page (struct hmm_range*,int) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

long hmm_range_dma_unmap(struct hmm_range *range,
			 struct device *device,
			 dma_addr_t *daddrs,
			 bool dirty)
{
	unsigned long i, npages;
	long cpages = 0;

	/* Sanity check. */
	if (range->end <= range->start)
		return -EINVAL;
	if (!daddrs)
		return -EINVAL;
	if (!range->pfns)
		return -EINVAL;

	npages = (range->end - range->start) >> PAGE_SHIFT;
	for (i = 0; i < npages; ++i) {
		enum dma_data_direction dir = DMA_TO_DEVICE;
		struct page *page;

		page = hmm_device_entry_to_page(range, range->pfns[i]);
		if (page == NULL)
			continue;

		/* If it is read and write than map bi-directional. */
		if (range->pfns[i] & range->flags[HMM_PFN_WRITE]) {
			dir = DMA_BIDIRECTIONAL;

			/*
			 * See comments in function description on why it is
			 * safe here to call set_page_dirty()
			 */
			if (dirty)
				set_page_dirty(page);
		}

		/* Unmap and clear pfns/dma address */
		dma_unmap_page(device, daddrs[i], PAGE_SIZE, dir);
		range->pfns[i] = range->values[HMM_PFN_NONE];
		/* FIXME see comments in hmm_vma_dma_map() */
		daddrs[i] = 0;
		cpages++;
	}

	return cpages;
}