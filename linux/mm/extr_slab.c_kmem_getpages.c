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
struct kmem_cache {int /*<<< orphan*/  gfporder; int /*<<< orphan*/  allocflags; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetPageSlabPfmemalloc (struct page*) ; 
 int /*<<< orphan*/  __SetPageSlab (struct page*) ; 
 struct page* __alloc_pages_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ charge_slab_page (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kmem_cache*) ; 
 scalar_t__ page_is_pfmemalloc (struct page*) ; 
 scalar_t__ sk_memalloc_socks () ; 
 int /*<<< orphan*/  slab_out_of_memory (struct kmem_cache*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct page *kmem_getpages(struct kmem_cache *cachep, gfp_t flags,
								int nodeid)
{
	struct page *page;

	flags |= cachep->allocflags;

	page = __alloc_pages_node(nodeid, flags, cachep->gfporder);
	if (!page) {
		slab_out_of_memory(cachep, flags, nodeid);
		return NULL;
	}

	if (charge_slab_page(page, flags, cachep->gfporder, cachep)) {
		__free_pages(page, cachep->gfporder);
		return NULL;
	}

	__SetPageSlab(page);
	/* Record if ALLOC_NO_WATERMARKS was set when allocating the slab */
	if (sk_memalloc_socks() && page_is_pfmemalloc(page))
		SetPageSlabPfmemalloc(page);

	return page;
}