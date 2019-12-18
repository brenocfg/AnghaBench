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
struct hmm_range {unsigned long end; unsigned long start; int* pfns; int* flags; int /*<<< orphan*/  valid; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DMA_BIDIRECTIONAL ; 
 int DMA_TO_DEVICE ; 
 long EBUSY ; 
 long EFAULT ; 
 size_t HMM_PFN_WRITE ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_map_page (struct device*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct page* hmm_device_entry_to_page (struct hmm_range*,int) ; 
 long hmm_range_fault (struct hmm_range*,unsigned int) ; 

long hmm_range_dma_map(struct hmm_range *range, struct device *device,
		dma_addr_t *daddrs, unsigned int flags)
{
	unsigned long i, npages, mapped;
	long ret;

	ret = hmm_range_fault(range, flags);
	if (ret <= 0)
		return ret ? ret : -EBUSY;

	npages = (range->end - range->start) >> PAGE_SHIFT;
	for (i = 0, mapped = 0; i < npages; ++i) {
		enum dma_data_direction dir = DMA_TO_DEVICE;
		struct page *page;

		/*
		 * FIXME need to update DMA API to provide invalid DMA address
		 * value instead of a function to test dma address value. This
		 * would remove lot of dumb code duplicated accross many arch.
		 *
		 * For now setting it to 0 here is good enough as the pfns[]
		 * value is what is use to check what is valid and what isn't.
		 */
		daddrs[i] = 0;

		page = hmm_device_entry_to_page(range, range->pfns[i]);
		if (page == NULL)
			continue;

		/* Check if range is being invalidated */
		if (!range->valid) {
			ret = -EBUSY;
			goto unmap;
		}

		/* If it is read and write than map bi-directional. */
		if (range->pfns[i] & range->flags[HMM_PFN_WRITE])
			dir = DMA_BIDIRECTIONAL;

		daddrs[i] = dma_map_page(device, page, 0, PAGE_SIZE, dir);
		if (dma_mapping_error(device, daddrs[i])) {
			ret = -EFAULT;
			goto unmap;
		}

		mapped++;
	}

	return mapped;

unmap:
	for (npages = i, i = 0; (i < npages) && mapped; ++i) {
		enum dma_data_direction dir = DMA_TO_DEVICE;
		struct page *page;

		page = hmm_device_entry_to_page(range, range->pfns[i]);
		if (page == NULL)
			continue;

		if (dma_mapping_error(device, daddrs[i]))
			continue;

		/* If it is read and write than map bi-directional. */
		if (range->pfns[i] & range->flags[HMM_PFN_WRITE])
			dir = DMA_BIDIRECTIONAL;

		dma_unmap_page(device, daddrs[i], PAGE_SIZE, dir);
		mapped--;
	}

	return ret;
}