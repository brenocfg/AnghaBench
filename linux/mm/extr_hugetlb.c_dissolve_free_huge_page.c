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
struct page {int /*<<< orphan*/  lru; } ;
struct hstate {scalar_t__ free_huge_pages; scalar_t__ resv_huge_pages; int /*<<< orphan*/  max_huge_pages; int /*<<< orphan*/ * free_huge_pages_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageHWPoison (struct page*) ; 
 int EBUSY ; 
 scalar_t__ PageHWPoison (struct page*) ; 
 int /*<<< orphan*/  PageHuge (struct page*) ; 
 int /*<<< orphan*/  SetPageHWPoison (struct page*) ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/  hugetlb_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_count (struct page*) ; 
 struct hstate* page_hstate (struct page*) ; 
 int page_to_nid (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_and_free_page (struct hstate*,struct page*) ; 

int dissolve_free_huge_page(struct page *page)
{
	int rc = -EBUSY;

	/* Not to disrupt normal path by vainly holding hugetlb_lock */
	if (!PageHuge(page))
		return 0;

	spin_lock(&hugetlb_lock);
	if (!PageHuge(page)) {
		rc = 0;
		goto out;
	}

	if (!page_count(page)) {
		struct page *head = compound_head(page);
		struct hstate *h = page_hstate(head);
		int nid = page_to_nid(head);
		if (h->free_huge_pages - h->resv_huge_pages == 0)
			goto out;
		/*
		 * Move PageHWPoison flag from head page to the raw error page,
		 * which makes any subpages rather than the error page reusable.
		 */
		if (PageHWPoison(head) && page != head) {
			SetPageHWPoison(page);
			ClearPageHWPoison(head);
		}
		list_del(&head->lru);
		h->free_huge_pages--;
		h->free_huge_pages_node[nid]--;
		h->max_huge_pages--;
		update_and_free_page(h, head);
		rc = 0;
	}
out:
	spin_unlock(&hugetlb_lock);
	return rc;
}