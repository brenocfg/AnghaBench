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
 int HPAGE_PMD_NR ; 
 int /*<<< orphan*/  NR_FILE_MAPPED ; 
 int /*<<< orphan*/  NR_FILE_PMDMAPPED ; 
 int /*<<< orphan*/  NR_SHMEM_PMDMAPPED ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 scalar_t__ PageMlocked (struct page*) ; 
 scalar_t__ PageSwapBacked (struct page*) ; 
 scalar_t__ PageTransCompound (struct page*) ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  SetPageDoubleMap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  VM_WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __inc_node_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mod_lruvec_page_state (struct page*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ atomic_inc_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_page_mlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compound_head (struct page*) ; 
 int /*<<< orphan*/ * compound_mapcount_ptr (struct page*) ; 
 int /*<<< orphan*/  lock_page_memcg (struct page*) ; 
 scalar_t__ page_mapping (struct page*) ; 
 int /*<<< orphan*/  unlock_page_memcg (struct page*) ; 

void page_add_file_rmap(struct page *page, bool compound)
{
	int i, nr = 1;

	VM_BUG_ON_PAGE(compound && !PageTransHuge(page), page);
	lock_page_memcg(page);
	if (compound && PageTransHuge(page)) {
		for (i = 0, nr = 0; i < HPAGE_PMD_NR; i++) {
			if (atomic_inc_and_test(&page[i]._mapcount))
				nr++;
		}
		if (!atomic_inc_and_test(compound_mapcount_ptr(page)))
			goto out;
		if (PageSwapBacked(page))
			__inc_node_page_state(page, NR_SHMEM_PMDMAPPED);
		else
			__inc_node_page_state(page, NR_FILE_PMDMAPPED);
	} else {
		if (PageTransCompound(page) && page_mapping(page)) {
			VM_WARN_ON_ONCE(!PageLocked(page));

			SetPageDoubleMap(compound_head(page));
			if (PageMlocked(page))
				clear_page_mlock(compound_head(page));
		}
		if (!atomic_inc_and_test(&page->_mapcount))
			goto out;
	}
	__mod_lruvec_page_state(page, NR_FILE_MAPPED, nr);
out:
	unlock_page_memcg(page);
}