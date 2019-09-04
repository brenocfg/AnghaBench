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
struct page_frag {int offset; int size; scalar_t__ page; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int SKB_FRAG_PAGE_ORDER ; 
 int __GFP_COMP ; 
 int __GFP_DIRECT_RECLAIM ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 scalar_t__ alloc_page (int) ; 
 scalar_t__ alloc_pages (int,int) ; 
 scalar_t__ likely (scalar_t__) ; 
 int page_ref_count (scalar_t__) ; 
 int /*<<< orphan*/  put_page (scalar_t__) ; 

bool skb_page_frag_refill(unsigned int sz, struct page_frag *pfrag, gfp_t gfp)
{
	if (pfrag->page) {
		if (page_ref_count(pfrag->page) == 1) {
			pfrag->offset = 0;
			return true;
		}
		if (pfrag->offset + sz <= pfrag->size)
			return true;
		put_page(pfrag->page);
	}

	pfrag->offset = 0;
	if (SKB_FRAG_PAGE_ORDER) {
		/* Avoid direct reclaim but allow kswapd to wake */
		pfrag->page = alloc_pages((gfp & ~__GFP_DIRECT_RECLAIM) |
					  __GFP_COMP | __GFP_NOWARN |
					  __GFP_NORETRY,
					  SKB_FRAG_PAGE_ORDER);
		if (likely(pfrag->page)) {
			pfrag->size = PAGE_SIZE << SKB_FRAG_PAGE_ORDER;
			return true;
		}
	}
	pfrag->page = alloc_page(gfp);
	if (likely(pfrag->page)) {
		pfrag->size = PAGE_SIZE;
		return true;
	}
	return false;
}