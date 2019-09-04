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
struct device {scalar_t__ coherent_dma_mask; } ;
typedef  int gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ARCH_ZONE_DMA_BITS ; 
 int /*<<< orphan*/  CONFIG_ZONE_DMA ; 
 int /*<<< orphan*/  CONFIG_ZONE_DMA32 ; 
 scalar_t__ DMA_BIT_MASK (int) ; 
 int GFP_DMA ; 
 int GFP_DMA32 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned int PAGE_ALIGN (size_t) ; 
 unsigned int PAGE_SHIFT ; 
 int __GFP_NOWARN ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_pages (struct page*,int) ; 
 int /*<<< orphan*/  __phys_to_dma (struct device*,int /*<<< orphan*/ ) ; 
 struct page* alloc_pages_node (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_to_node (struct device*) ; 
 struct page* dma_alloc_from_contiguous (struct device*,unsigned int,int,int) ; 
 int /*<<< orphan*/  dma_coherent_ok (struct device*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dma_release_from_contiguous (struct device*,struct page*,unsigned int) ; 
 scalar_t__ force_dma_unencrypted () ; 
 int get_order (size_t) ; 
 scalar_t__ gfpflags_allow_blocking (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 
 int /*<<< orphan*/  phys_to_dma (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_memory_decrypted (unsigned long,int) ; 

void *dma_direct_alloc(struct device *dev, size_t size, dma_addr_t *dma_handle,
		gfp_t gfp, unsigned long attrs)
{
	unsigned int count = PAGE_ALIGN(size) >> PAGE_SHIFT;
	int page_order = get_order(size);
	struct page *page = NULL;
	void *ret;

	/* we always manually zero the memory once we are done: */
	gfp &= ~__GFP_ZERO;

	/* GFP_DMA32 and GFP_DMA are no ops without the corresponding zones: */
	if (dev->coherent_dma_mask <= DMA_BIT_MASK(ARCH_ZONE_DMA_BITS))
		gfp |= GFP_DMA;
	if (dev->coherent_dma_mask <= DMA_BIT_MASK(32) && !(gfp & GFP_DMA))
		gfp |= GFP_DMA32;

again:
	/* CMA can be used only in the context which permits sleeping */
	if (gfpflags_allow_blocking(gfp)) {
		page = dma_alloc_from_contiguous(dev, count, page_order,
						 gfp & __GFP_NOWARN);
		if (page && !dma_coherent_ok(dev, page_to_phys(page), size)) {
			dma_release_from_contiguous(dev, page, count);
			page = NULL;
		}
	}
	if (!page)
		page = alloc_pages_node(dev_to_node(dev), gfp, page_order);

	if (page && !dma_coherent_ok(dev, page_to_phys(page), size)) {
		__free_pages(page, page_order);
		page = NULL;

		if (IS_ENABLED(CONFIG_ZONE_DMA32) &&
		    dev->coherent_dma_mask < DMA_BIT_MASK(64) &&
		    !(gfp & (GFP_DMA32 | GFP_DMA))) {
			gfp |= GFP_DMA32;
			goto again;
		}

		if (IS_ENABLED(CONFIG_ZONE_DMA) &&
		    dev->coherent_dma_mask < DMA_BIT_MASK(32) &&
		    !(gfp & GFP_DMA)) {
			gfp = (gfp & ~GFP_DMA32) | GFP_DMA;
			goto again;
		}
	}

	if (!page)
		return NULL;
	ret = page_address(page);
	if (force_dma_unencrypted()) {
		set_memory_decrypted((unsigned long)ret, 1 << page_order);
		*dma_handle = __phys_to_dma(dev, page_to_phys(page));
	} else {
		*dma_handle = phys_to_dma(dev, page_to_phys(page));
	}
	memset(ret, 0, size);
	return ret;
}