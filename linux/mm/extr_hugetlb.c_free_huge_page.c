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
struct page {int /*<<< orphan*/  lru; int /*<<< orphan*/ * mapping; } ;
struct hugepage_subpool {int dummy; } ;
struct hstate {scalar_t__* surplus_huge_pages_node; int /*<<< orphan*/  surplus_huge_pages; int /*<<< orphan*/  resv_huge_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageHugeTemporary (struct page*) ; 
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 scalar_t__ PageHugeTemporary (struct page*) ; 
 int PagePrivate (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  arch_clear_hugepage_flags (struct page*) ; 
 int /*<<< orphan*/  clear_page_huge_active (struct page*) ; 
 int /*<<< orphan*/  enqueue_huge_page (struct hstate*,struct page*) ; 
 int /*<<< orphan*/  hstate_index (struct hstate*) ; 
 scalar_t__ hugepage_subpool_put_pages (struct hugepage_subpool*,int) ; 
 int /*<<< orphan*/  hugetlb_cgroup_uncharge_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  hugetlb_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_count (struct page*) ; 
 struct hstate* page_hstate (struct page*) ; 
 int /*<<< orphan*/  page_mapcount (struct page*) ; 
 scalar_t__ page_private (struct page*) ; 
 int page_to_nid (struct page*) ; 
 int /*<<< orphan*/  pages_per_huge_page (struct hstate*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_and_free_page (struct hstate*,struct page*) ; 

void free_huge_page(struct page *page)
{
	/*
	 * Can't pass hstate in here because it is called from the
	 * compound page destructor.
	 */
	struct hstate *h = page_hstate(page);
	int nid = page_to_nid(page);
	struct hugepage_subpool *spool =
		(struct hugepage_subpool *)page_private(page);
	bool restore_reserve;

	VM_BUG_ON_PAGE(page_count(page), page);
	VM_BUG_ON_PAGE(page_mapcount(page), page);

	set_page_private(page, 0);
	page->mapping = NULL;
	restore_reserve = PagePrivate(page);
	ClearPagePrivate(page);

	/*
	 * If PagePrivate() was set on page, page allocation consumed a
	 * reservation.  If the page was associated with a subpool, there
	 * would have been a page reserved in the subpool before allocation
	 * via hugepage_subpool_get_pages().  Since we are 'restoring' the
	 * reservtion, do not call hugepage_subpool_put_pages() as this will
	 * remove the reserved page from the subpool.
	 */
	if (!restore_reserve) {
		/*
		 * A return code of zero implies that the subpool will be
		 * under its minimum size if the reservation is not restored
		 * after page is free.  Therefore, force restore_reserve
		 * operation.
		 */
		if (hugepage_subpool_put_pages(spool, 1) == 0)
			restore_reserve = true;
	}

	spin_lock(&hugetlb_lock);
	clear_page_huge_active(page);
	hugetlb_cgroup_uncharge_page(hstate_index(h),
				     pages_per_huge_page(h), page);
	if (restore_reserve)
		h->resv_huge_pages++;

	if (PageHugeTemporary(page)) {
		list_del(&page->lru);
		ClearPageHugeTemporary(page);
		update_and_free_page(h, page);
	} else if (h->surplus_huge_pages_node[nid]) {
		/* remove the page from active list */
		list_del(&page->lru);
		update_and_free_page(h, page);
		h->surplus_huge_pages--;
		h->surplus_huge_pages_node[nid]--;
	} else {
		arch_clear_hugepage_flags(page);
		enqueue_huge_page(h, page);
	}
	spin_unlock(&hugetlb_lock);
}