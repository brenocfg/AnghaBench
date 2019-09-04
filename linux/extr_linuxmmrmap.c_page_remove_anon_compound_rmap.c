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
struct page {int /*<<< orphan*/  _mapcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_TRANSPARENT_HUGEPAGE ; 
 int HPAGE_PMD_NR ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NR_ANON_MAPPED ; 
 int /*<<< orphan*/  NR_ANON_THPS ; 
 int /*<<< orphan*/  PageHuge (struct page*) ; 
 int /*<<< orphan*/  PageMlocked (struct page*) ; 
 scalar_t__ TestClearPageDoubleMap (struct page*) ; 
 int /*<<< orphan*/  __dec_node_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mod_node_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ atomic_add_negative (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_page_mlock (struct page*) ; 
 int /*<<< orphan*/ * compound_mapcount_ptr (struct page*) ; 
 int /*<<< orphan*/  deferred_split_huge_page (struct page*) ; 
 int /*<<< orphan*/  page_pgdat (struct page*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void page_remove_anon_compound_rmap(struct page *page)
{
	int i, nr;

	if (!atomic_add_negative(-1, compound_mapcount_ptr(page)))
		return;

	/* Hugepages are not counted in NR_ANON_PAGES for now. */
	if (unlikely(PageHuge(page)))
		return;

	if (!IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE))
		return;

	__dec_node_page_state(page, NR_ANON_THPS);

	if (TestClearPageDoubleMap(page)) {
		/*
		 * Subpages can be mapped with PTEs too. Check how many of
		 * themi are still mapped.
		 */
		for (i = 0, nr = 0; i < HPAGE_PMD_NR; i++) {
			if (atomic_add_negative(-1, &page[i]._mapcount))
				nr++;
		}
	} else {
		nr = HPAGE_PMD_NR;
	}

	if (unlikely(PageMlocked(page)))
		clear_page_mlock(page);

	if (nr) {
		__mod_node_page_state(page_pgdat(page), NR_ANON_MAPPED, -nr);
		deferred_split_huge_page(page);
	}
}