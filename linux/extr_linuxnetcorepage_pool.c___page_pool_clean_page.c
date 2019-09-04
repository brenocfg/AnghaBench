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
struct page_pool {TYPE_1__ p; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int PP_FLAG_DMA_MAP ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __page_pool_clean_page(struct page_pool *pool,
				   struct page *page)
{
	if (!(pool->p.flags & PP_FLAG_DMA_MAP))
		return;

	/* DMA unmap */
	dma_unmap_page(pool->p.dev, page_private(page),
		       PAGE_SIZE << pool->p.order, pool->p.dma_dir);
	set_page_private(page, 0);
}