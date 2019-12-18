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
struct page_frag_cache {int /*<<< orphan*/ * va; int /*<<< orphan*/  size; } ;
struct page {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int /*<<< orphan*/  PAGE_FRAG_CACHE_MAX_ORDER ; 
 int /*<<< orphan*/  PAGE_FRAG_CACHE_MAX_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __GFP_COMP ; 
 int __GFP_NOMEMALLOC ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 struct page* alloc_pages_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * page_address (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct page *__page_frag_cache_refill(struct page_frag_cache *nc,
					     gfp_t gfp_mask)
{
	struct page *page = NULL;
	gfp_t gfp = gfp_mask;

#if (PAGE_SIZE < PAGE_FRAG_CACHE_MAX_SIZE)
	gfp_mask |= __GFP_COMP | __GFP_NOWARN | __GFP_NORETRY |
		    __GFP_NOMEMALLOC;
	page = alloc_pages_node(NUMA_NO_NODE, gfp_mask,
				PAGE_FRAG_CACHE_MAX_ORDER);
	nc->size = page ? PAGE_FRAG_CACHE_MAX_SIZE : PAGE_SIZE;
#endif
	if (unlikely(!page))
		page = alloc_pages_node(NUMA_NO_NODE, gfp, 0);

	nc->va = page ? page_address(page) : NULL;

	return page;
}