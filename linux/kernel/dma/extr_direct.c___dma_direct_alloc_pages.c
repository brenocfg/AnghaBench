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
typedef  scalar_t__ u64 ;
struct page {int dummy; } ;
struct device {int /*<<< orphan*/  coherent_dma_mask; } ;
typedef  int gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ZONE_DMA ; 
 int /*<<< orphan*/  CONFIG_ZONE_DMA32 ; 
 unsigned long DMA_ATTR_NO_WARN ; 
 scalar_t__ DMA_BIT_MASK (int) ; 
 int GFP_DMA ; 
 int GFP_DMA32 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 size_t PAGE_ALIGN (size_t) ; 
 int __GFP_NOWARN ; 
 int __GFP_ZERO ; 
 int __dma_direct_optimal_gfp_mask (struct device*,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct page* alloc_pages_node (int,int,int /*<<< orphan*/ ) ; 
 int dev_to_node (struct device*) ; 
 struct page* dma_alloc_contiguous (struct device*,size_t,int) ; 
 int /*<<< orphan*/  dma_coherent_ok (struct device*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dma_free_contiguous (struct device*,struct page*,size_t) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 

struct page *__dma_direct_alloc_pages(struct device *dev, size_t size,
		dma_addr_t *dma_handle, gfp_t gfp, unsigned long attrs)
{
	size_t alloc_size = PAGE_ALIGN(size);
	int node = dev_to_node(dev);
	struct page *page = NULL;
	u64 phys_mask;

	if (attrs & DMA_ATTR_NO_WARN)
		gfp |= __GFP_NOWARN;

	/* we always manually zero the memory once we are done: */
	gfp &= ~__GFP_ZERO;
	gfp |= __dma_direct_optimal_gfp_mask(dev, dev->coherent_dma_mask,
			&phys_mask);
	page = dma_alloc_contiguous(dev, alloc_size, gfp);
	if (page && !dma_coherent_ok(dev, page_to_phys(page), size)) {
		dma_free_contiguous(dev, page, alloc_size);
		page = NULL;
	}
again:
	if (!page)
		page = alloc_pages_node(node, gfp, get_order(alloc_size));
	if (page && !dma_coherent_ok(dev, page_to_phys(page), size)) {
		dma_free_contiguous(dev, page, size);
		page = NULL;

		if (IS_ENABLED(CONFIG_ZONE_DMA32) &&
		    phys_mask < DMA_BIT_MASK(64) &&
		    !(gfp & (GFP_DMA32 | GFP_DMA))) {
			gfp |= GFP_DMA32;
			goto again;
		}

		if (IS_ENABLED(CONFIG_ZONE_DMA) && !(gfp & GFP_DMA)) {
			gfp = (gfp & ~GFP_DMA32) | GFP_DMA;
			goto again;
		}
	}

	return page;
}