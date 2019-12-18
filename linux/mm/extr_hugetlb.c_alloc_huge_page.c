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
struct vm_area_struct {int dummy; } ;
struct page {int /*<<< orphan*/  lru; } ;
struct hugetlb_cgroup {int dummy; } ;
struct hugepage_subpool {int dummy; } ;
struct hstate {int /*<<< orphan*/  hugepage_activelist; int /*<<< orphan*/  resv_huge_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSPC ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPagePrivate (struct page*) ; 
 struct page* alloc_buddy_huge_page_with_mpol (struct hstate*,struct vm_area_struct*,unsigned long) ; 
 struct page* dequeue_huge_page_vma (struct hstate*,struct vm_area_struct*,unsigned long,int,long) ; 
 int hstate_index (struct hstate*) ; 
 struct hstate* hstate_vma (struct vm_area_struct*) ; 
 long hugepage_subpool_get_pages (struct hugepage_subpool*,int) ; 
 long hugepage_subpool_put_pages (struct hugepage_subpool*,int) ; 
 int /*<<< orphan*/  hugetlb_acct_memory (struct hstate*,long) ; 
 int hugetlb_cgroup_charge_cgroup (int,int /*<<< orphan*/ ,struct hugetlb_cgroup**) ; 
 int /*<<< orphan*/  hugetlb_cgroup_commit_charge (int,int /*<<< orphan*/ ,struct hugetlb_cgroup*,struct page*) ; 
 int /*<<< orphan*/  hugetlb_cgroup_uncharge_cgroup (int,int /*<<< orphan*/ ,struct hugetlb_cgroup*) ; 
 int /*<<< orphan*/  hugetlb_lock ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pages_per_huge_page (struct hstate*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct hugepage_subpool* subpool_vma (struct vm_area_struct*) ; 
 scalar_t__ unlikely (int) ; 
 long vma_commit_reservation (struct hstate*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  vma_end_reservation (struct hstate*,struct vm_area_struct*,unsigned long) ; 
 scalar_t__ vma_has_reserves (struct vm_area_struct*,long) ; 
 long vma_needs_reservation (struct hstate*,struct vm_area_struct*,unsigned long) ; 

struct page *alloc_huge_page(struct vm_area_struct *vma,
				    unsigned long addr, int avoid_reserve)
{
	struct hugepage_subpool *spool = subpool_vma(vma);
	struct hstate *h = hstate_vma(vma);
	struct page *page;
	long map_chg, map_commit;
	long gbl_chg;
	int ret, idx;
	struct hugetlb_cgroup *h_cg;

	idx = hstate_index(h);
	/*
	 * Examine the region/reserve map to determine if the process
	 * has a reservation for the page to be allocated.  A return
	 * code of zero indicates a reservation exists (no change).
	 */
	map_chg = gbl_chg = vma_needs_reservation(h, vma, addr);
	if (map_chg < 0)
		return ERR_PTR(-ENOMEM);

	/*
	 * Processes that did not create the mapping will have no
	 * reserves as indicated by the region/reserve map. Check
	 * that the allocation will not exceed the subpool limit.
	 * Allocations for MAP_NORESERVE mappings also need to be
	 * checked against any subpool limit.
	 */
	if (map_chg || avoid_reserve) {
		gbl_chg = hugepage_subpool_get_pages(spool, 1);
		if (gbl_chg < 0) {
			vma_end_reservation(h, vma, addr);
			return ERR_PTR(-ENOSPC);
		}

		/*
		 * Even though there was no reservation in the region/reserve
		 * map, there could be reservations associated with the
		 * subpool that can be used.  This would be indicated if the
		 * return value of hugepage_subpool_get_pages() is zero.
		 * However, if avoid_reserve is specified we still avoid even
		 * the subpool reservations.
		 */
		if (avoid_reserve)
			gbl_chg = 1;
	}

	ret = hugetlb_cgroup_charge_cgroup(idx, pages_per_huge_page(h), &h_cg);
	if (ret)
		goto out_subpool_put;

	spin_lock(&hugetlb_lock);
	/*
	 * glb_chg is passed to indicate whether or not a page must be taken
	 * from the global free pool (global change).  gbl_chg == 0 indicates
	 * a reservation exists for the allocation.
	 */
	page = dequeue_huge_page_vma(h, vma, addr, avoid_reserve, gbl_chg);
	if (!page) {
		spin_unlock(&hugetlb_lock);
		page = alloc_buddy_huge_page_with_mpol(h, vma, addr);
		if (!page)
			goto out_uncharge_cgroup;
		if (!avoid_reserve && vma_has_reserves(vma, gbl_chg)) {
			SetPagePrivate(page);
			h->resv_huge_pages--;
		}
		spin_lock(&hugetlb_lock);
		list_move(&page->lru, &h->hugepage_activelist);
		/* Fall through */
	}
	hugetlb_cgroup_commit_charge(idx, pages_per_huge_page(h), h_cg, page);
	spin_unlock(&hugetlb_lock);

	set_page_private(page, (unsigned long)spool);

	map_commit = vma_commit_reservation(h, vma, addr);
	if (unlikely(map_chg > map_commit)) {
		/*
		 * The page was added to the reservation map between
		 * vma_needs_reservation and vma_commit_reservation.
		 * This indicates a race with hugetlb_reserve_pages.
		 * Adjust for the subpool count incremented above AND
		 * in hugetlb_reserve_pages for the same page.  Also,
		 * the reservation count added in hugetlb_reserve_pages
		 * no longer applies.
		 */
		long rsv_adjust;

		rsv_adjust = hugepage_subpool_put_pages(spool, 1);
		hugetlb_acct_memory(h, -rsv_adjust);
	}
	return page;

out_uncharge_cgroup:
	hugetlb_cgroup_uncharge_cgroup(idx, pages_per_huge_page(h), h_cg);
out_subpool_put:
	if (map_chg || avoid_reserve)
		hugepage_subpool_put_pages(spool, 1);
	vma_end_reservation(h, vma, addr);
	return ERR_PTR(-ENOSPC);
}