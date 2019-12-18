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
struct hstate {scalar_t__ resv_huge_pages; int /*<<< orphan*/  surplus_huge_pages; } ;

/* Variables and functions */
 size_t N_MEMORY ; 
 int /*<<< orphan*/  cond_resched_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pool_huge_page (struct hstate*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ hstate_is_gigantic (struct hstate*) ; 
 int /*<<< orphan*/  hugetlb_lock ; 
 unsigned long min (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * node_states ; 

__attribute__((used)) static void return_unused_surplus_pages(struct hstate *h,
					unsigned long unused_resv_pages)
{
	unsigned long nr_pages;

	/* Cannot return gigantic pages currently */
	if (hstate_is_gigantic(h))
		goto out;

	/*
	 * Part (or even all) of the reservation could have been backed
	 * by pre-allocated pages. Only free surplus pages.
	 */
	nr_pages = min(unused_resv_pages, h->surplus_huge_pages);

	/*
	 * We want to release as many surplus pages as possible, spread
	 * evenly across all nodes with memory. Iterate across these nodes
	 * until we can no longer free unreserved surplus pages. This occurs
	 * when the nodes with surplus pages have no free pages.
	 * free_pool_huge_page() will balance the the freed pages across the
	 * on-line nodes with memory and will handle the hstate accounting.
	 *
	 * Note that we decrement resv_huge_pages as we free the pages.  If
	 * we drop the lock, resv_huge_pages will still be sufficiently large
	 * to cover subsequent pages we may free.
	 */
	while (nr_pages--) {
		h->resv_huge_pages--;
		unused_resv_pages--;
		if (!free_pool_huge_page(h, &node_states[N_MEMORY], 1))
			goto out;
		cond_resched_lock(&hugetlb_lock);
	}

out:
	/* Fully uncommit the reservation */
	h->resv_huge_pages -= unused_resv_pages;
}