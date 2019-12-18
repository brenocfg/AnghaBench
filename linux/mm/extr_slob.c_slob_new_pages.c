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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  NR_SLAB_UNRECLAIMABLE ; 
 int NUMA_NO_NODE ; 
 struct page* __alloc_pages_node (int,int /*<<< orphan*/ ,int) ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_node_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  page_pgdat (struct page*) ; 

__attribute__((used)) static void *slob_new_pages(gfp_t gfp, int order, int node)
{
	struct page *page;

#ifdef CONFIG_NUMA
	if (node != NUMA_NO_NODE)
		page = __alloc_pages_node(node, gfp, order);
	else
#endif
		page = alloc_pages(gfp, order);

	if (!page)
		return NULL;

	mod_node_page_state(page_pgdat(page), NR_SLAB_UNRECLAIMABLE,
			    1 << order);
	return page_address(page);
}