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
typedef  void page ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARCH_HAS_UNCACHED_SEGMENT ; 
 unsigned long DMA_ATTR_NO_KERNEL_MAPPING ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ PageHighMem (void*) ; 
 void* __dma_direct_alloc_pages (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  __dma_direct_free_pages (struct device*,size_t,void*) ; 
 int /*<<< orphan*/  __phys_to_dma (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_dma_prep_coherent (void*,size_t) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 scalar_t__ dma_alloc_need_uncached (struct device*,unsigned long) ; 
 scalar_t__ force_dma_unencrypted (struct device*) ; 
 int get_order (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 void* page_address (void*) ; 
 int /*<<< orphan*/  page_to_phys (void*) ; 
 int /*<<< orphan*/  phys_to_dma (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_memory_decrypted (unsigned long,int) ; 
 void* uncached_kernel_address (void*) ; 

void *dma_direct_alloc_pages(struct device *dev, size_t size,
		dma_addr_t *dma_handle, gfp_t gfp, unsigned long attrs)
{
	struct page *page;
	void *ret;

	page = __dma_direct_alloc_pages(dev, size, dma_handle, gfp, attrs);
	if (!page)
		return NULL;

	if ((attrs & DMA_ATTR_NO_KERNEL_MAPPING) &&
	    !force_dma_unencrypted(dev)) {
		/* remove any dirty cache lines on the kernel alias */
		if (!PageHighMem(page))
			arch_dma_prep_coherent(page, size);
		*dma_handle = phys_to_dma(dev, page_to_phys(page));
		/* return the page pointer as the opaque cookie */
		return page;
	}

	if (PageHighMem(page)) {
		/*
		 * Depending on the cma= arguments and per-arch setup
		 * dma_alloc_contiguous could return highmem pages.
		 * Without remapping there is no way to return them here,
		 * so log an error and fail.
		 */
		dev_info(dev, "Rejecting highmem page from CMA.\n");
		__dma_direct_free_pages(dev, size, page);
		return NULL;
	}

	ret = page_address(page);
	if (force_dma_unencrypted(dev)) {
		set_memory_decrypted((unsigned long)ret, 1 << get_order(size));
		*dma_handle = __phys_to_dma(dev, page_to_phys(page));
	} else {
		*dma_handle = phys_to_dma(dev, page_to_phys(page));
	}
	memset(ret, 0, size);

	if (IS_ENABLED(CONFIG_ARCH_HAS_UNCACHED_SEGMENT) &&
	    dma_alloc_need_uncached(dev, attrs)) {
		arch_dma_prep_coherent(page, size);
		ret = uncached_kernel_address(ret);
	}

	return ret;
}