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
struct page {int flags; } ;
struct hstate {int /*<<< orphan*/ * nr_huge_pages_node; int /*<<< orphan*/  nr_huge_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_COMPOUND_DTOR ; 
 int PG_active ; 
 int PG_dirty ; 
 int PG_error ; 
 int PG_locked ; 
 int PG_private ; 
 int PG_referenced ; 
 int PG_writeback ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_compound_gigantic_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_gigantic_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gigantic_page_runtime_supported () ; 
 scalar_t__ hstate_is_gigantic (struct hstate*) ; 
 int /*<<< orphan*/  huge_page_order (struct hstate*) ; 
 int /*<<< orphan*/  hugetlb_cgroup_from_page (struct page*) ; 
 size_t page_to_nid (struct page*) ; 
 int pages_per_huge_page (struct hstate*) ; 
 int /*<<< orphan*/  set_compound_page_dtor (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_refcounted (struct page*) ; 

__attribute__((used)) static void update_and_free_page(struct hstate *h, struct page *page)
{
	int i;

	if (hstate_is_gigantic(h) && !gigantic_page_runtime_supported())
		return;

	h->nr_huge_pages--;
	h->nr_huge_pages_node[page_to_nid(page)]--;
	for (i = 0; i < pages_per_huge_page(h); i++) {
		page[i].flags &= ~(1 << PG_locked | 1 << PG_error |
				1 << PG_referenced | 1 << PG_dirty |
				1 << PG_active | 1 << PG_private |
				1 << PG_writeback);
	}
	VM_BUG_ON_PAGE(hugetlb_cgroup_from_page(page), page);
	set_compound_page_dtor(page, NULL_COMPOUND_DTOR);
	set_page_refcounted(page);
	if (hstate_is_gigantic(h)) {
		destroy_compound_gigantic_page(page, huge_page_order(h));
		free_gigantic_page(page, huge_page_order(h));
	} else {
		__free_pages(page, huge_page_order(h));
	}
}