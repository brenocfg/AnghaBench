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
struct hstate {scalar_t__ surplus_huge_pages; scalar_t__ nr_overcommit_huge_pages; int /*<<< orphan*/ * surplus_huge_pages_node; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetPageHugeTemporary (struct page*) ; 
 struct page* alloc_fresh_huge_page (struct hstate*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hstate_is_gigantic (struct hstate*) ; 
 int /*<<< orphan*/  hugetlb_lock ; 
 size_t page_to_nid (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *alloc_surplus_huge_page(struct hstate *h, gfp_t gfp_mask,
		int nid, nodemask_t *nmask)
{
	struct page *page = NULL;

	if (hstate_is_gigantic(h))
		return NULL;

	spin_lock(&hugetlb_lock);
	if (h->surplus_huge_pages >= h->nr_overcommit_huge_pages)
		goto out_unlock;
	spin_unlock(&hugetlb_lock);

	page = alloc_fresh_huge_page(h, gfp_mask, nid, nmask, NULL);
	if (!page)
		return NULL;

	spin_lock(&hugetlb_lock);
	/*
	 * We could have raced with the pool size change.
	 * Double check that and simply deallocate the new page
	 * if we would end up overcommiting the surpluses. Abuse
	 * temporary page to workaround the nasty free_huge_page
	 * codeflow
	 */
	if (h->surplus_huge_pages >= h->nr_overcommit_huge_pages) {
		SetPageHugeTemporary(page);
		spin_unlock(&hugetlb_lock);
		put_page(page);
		return NULL;
	} else {
		h->surplus_huge_pages++;
		h->surplus_huge_pages_node[page_to_nid(page)]++;
	}

out_unlock:
	spin_unlock(&hugetlb_lock);

	return page;
}