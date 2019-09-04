#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/ * mapping; } ;
struct kmem_cache {int gfporder; int flags; } ;
struct TYPE_4__ {TYPE_1__* reclaim_state; } ;
struct TYPE_3__ {unsigned long reclaimed_slab; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NR_SLAB_RECLAIMABLE ; 
 int /*<<< orphan*/  NR_SLAB_UNRECLAIMABLE ; 
 int /*<<< orphan*/  PageSlab (struct page*) ; 
 int SLAB_RECLAIM_ACCOUNT ; 
 int /*<<< orphan*/  __ClearPageSlab (struct page*) ; 
 int /*<<< orphan*/  __ClearPageSlabPfmemalloc (struct page*) ; 
 int /*<<< orphan*/  __free_pages (struct page*,int) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  memcg_uncharge_slab (struct page*,int,struct kmem_cache*) ; 
 int /*<<< orphan*/  mod_lruvec_page_state (struct page*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  page_mapcount_reset (struct page*) ; 

__attribute__((used)) static void kmem_freepages(struct kmem_cache *cachep, struct page *page)
{
	int order = cachep->gfporder;
	unsigned long nr_freed = (1 << order);

	if (cachep->flags & SLAB_RECLAIM_ACCOUNT)
		mod_lruvec_page_state(page, NR_SLAB_RECLAIMABLE, -nr_freed);
	else
		mod_lruvec_page_state(page, NR_SLAB_UNRECLAIMABLE, -nr_freed);

	BUG_ON(!PageSlab(page));
	__ClearPageSlabPfmemalloc(page);
	__ClearPageSlab(page);
	page_mapcount_reset(page);
	page->mapping = NULL;

	if (current->reclaim_state)
		current->reclaim_state->reclaimed_slab += nr_freed;
	memcg_uncharge_slab(page, order, cachep);
	__free_pages(page, order);
}