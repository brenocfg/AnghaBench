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
struct TYPE_2__ {int flags; int order; int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  dev; } ;
struct page_pool {int /*<<< orphan*/  pages_state_release_cnt; TYPE_1__ p; } ;
struct page {scalar_t__ dma_addr; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_SKIP_CPU_SYNC ; 
 int PAGE_SIZE ; 
 int PP_FLAG_DMA_MAP ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page_attrs (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_page_pool_state_release (struct page_pool*,struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __page_pool_clean_page(struct page_pool *pool,
				   struct page *page)
{
	dma_addr_t dma;

	if (!(pool->p.flags & PP_FLAG_DMA_MAP))
		goto skip_dma_unmap;

	dma = page->dma_addr;
	/* DMA unmap */
	dma_unmap_page_attrs(pool->p.dev, dma,
			     PAGE_SIZE << pool->p.order, pool->p.dma_dir,
			     DMA_ATTR_SKIP_CPU_SYNC);
	page->dma_addr = 0;
skip_dma_unmap:
	atomic_inc(&pool->pages_state_release_cnt);
	trace_page_pool_state_release(pool, page,
			      atomic_read(&pool->pages_state_release_cnt));
}