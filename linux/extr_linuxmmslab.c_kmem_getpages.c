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
struct kmem_cache {int gfporder; int flags; int /*<<< orphan*/  allocflags; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  NR_SLAB_RECLAIMABLE ; 
 int /*<<< orphan*/  NR_SLAB_UNRECLAIMABLE ; 
 int SLAB_RECLAIM_ACCOUNT ; 
 int /*<<< orphan*/  SetPageSlabPfmemalloc (struct page*) ; 
 int /*<<< orphan*/  __SetPageSlab (struct page*) ; 
 struct page* __alloc_pages_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __free_pages (struct page*,int) ; 
 scalar_t__ memcg_charge_slab (struct page*,int /*<<< orphan*/ ,int,struct kmem_cache*) ; 
 int /*<<< orphan*/  mod_lruvec_page_state (struct page*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ page_is_pfmemalloc (struct page*) ; 
 scalar_t__ sk_memalloc_socks () ; 
 int /*<<< orphan*/  slab_out_of_memory (struct kmem_cache*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct page *kmem_getpages(struct kmem_cache *cachep, gfp_t flags,
								int nodeid)
{
	struct page *page;
	int nr_pages;

	flags |= cachep->allocflags;

	page = __alloc_pages_node(nodeid, flags, cachep->gfporder);
	if (!page) {
		slab_out_of_memory(cachep, flags, nodeid);
		return NULL;
	}

	if (memcg_charge_slab(page, flags, cachep->gfporder, cachep)) {
		__free_pages(page, cachep->gfporder);
		return NULL;
	}

	nr_pages = (1 << cachep->gfporder);
	if (cachep->flags & SLAB_RECLAIM_ACCOUNT)
		mod_lruvec_page_state(page, NR_SLAB_RECLAIMABLE, nr_pages);
	else
		mod_lruvec_page_state(page, NR_SLAB_UNRECLAIMABLE, nr_pages);

	__SetPageSlab(page);
	/* Record if ALLOC_NO_WATERMARKS was set when allocating the slab */
	if (sk_memalloc_socks() && page_is_pfmemalloc(page))
		SetPageSlabPfmemalloc(page);

	return page;
}