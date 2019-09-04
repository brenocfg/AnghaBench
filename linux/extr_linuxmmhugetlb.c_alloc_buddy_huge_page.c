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
struct hstate {int dummy; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  HTLB_BUDDY_PGALLOC ; 
 int /*<<< orphan*/  HTLB_BUDDY_PGALLOC_FAIL ; 
 int NUMA_NO_NODE ; 
 int __GFP_COMP ; 
 int __GFP_NOWARN ; 
 int __GFP_RETRY_MAYFAIL ; 
 struct page* __alloc_pages_nodemask (int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __count_vm_event (int /*<<< orphan*/ ) ; 
 int huge_page_order (struct hstate*) ; 
 int numa_mem_id () ; 

__attribute__((used)) static struct page *alloc_buddy_huge_page(struct hstate *h,
		gfp_t gfp_mask, int nid, nodemask_t *nmask)
{
	int order = huge_page_order(h);
	struct page *page;

	gfp_mask |= __GFP_COMP|__GFP_RETRY_MAYFAIL|__GFP_NOWARN;
	if (nid == NUMA_NO_NODE)
		nid = numa_mem_id();
	page = __alloc_pages_nodemask(gfp_mask, order, nid, nmask);
	if (page)
		__count_vm_event(HTLB_BUDDY_PGALLOC);
	else
		__count_vm_event(HTLB_BUDDY_PGALLOC_FAIL);

	return page;
}