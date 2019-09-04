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
struct hstate {scalar_t__ free_huge_pages; scalar_t__ resv_huge_pages; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct page* alloc_migrate_huge_page (struct hstate*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct page* dequeue_huge_page_nodemask (struct hstate*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htlb_alloc_mask (struct hstate*) ; 
 int /*<<< orphan*/  hugetlb_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct page *alloc_huge_page_nodemask(struct hstate *h, int preferred_nid,
		nodemask_t *nmask)
{
	gfp_t gfp_mask = htlb_alloc_mask(h);

	spin_lock(&hugetlb_lock);
	if (h->free_huge_pages - h->resv_huge_pages > 0) {
		struct page *page;

		page = dequeue_huge_page_nodemask(h, gfp_mask, preferred_nid, nmask);
		if (page) {
			spin_unlock(&hugetlb_lock);
			return page;
		}
	}
	spin_unlock(&hugetlb_lock);

	return alloc_migrate_huge_page(h, gfp_mask, preferred_nid, nmask);
}