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
 int /*<<< orphan*/  PageHead (struct page*) ; 
 int /*<<< orphan*/  PageHuge (struct page*) ; 
 int /*<<< orphan*/  PageMlocked (struct page*) ; 
 scalar_t__ PageSwapBacked (struct page*) ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  __dec_node_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mod_lruvec_page_state (struct page*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ atomic_add_negative (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_page_mlock (struct page*) ; 
 int /*<<< orphan*/ * compound_mapcount_ptr (struct page*) ; 
 int /*<<< orphan*/  lock_page_memcg (struct page*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page_memcg (struct page*) ; 

__attribute__((used)) static void page_remove_file_rmap(struct page *page, bool compound)
{
	int i, nr = 1;

	VM_BUG_ON_PAGE(compound && !PageHead(page), page);
	lock_page_memcg(page);

	/* Hugepages are not counted in NR_FILE_MAPPED for now. */
	if (unlikely(PageHuge(page))) {
		/* hugetlb pages are always mapped with pmds */
		atomic_dec(compound_mapcount_ptr(page));
		goto out;
	}

	/* page still mapped by someone else? */
	if (compound && PageTransHuge(page)) {
		for (i = 0, nr = 0; i < HPAGE_PMD_NR; i++) {
			if (atomic_add_negative(-1, &page[i]._mapcount))
				nr++;
		}
		if (!atomic_add_negative(-1, compound_mapcount_ptr(page)))
			goto out;
		if (PageSwapBacked(page))
			__dec_node_page_state(page, NR_SHMEM_PMDMAPPED);
		else
			__dec_node_page_state(page, NR_FILE_PMDMAPPED);
	} else {
		if (!atomic_add_negative(-1, &page->_mapcount))
			goto out;
	}

	/*
	 * We use the irq-unsafe __{inc|mod}_lruvec_page_state because
	 * these counters are not modified in interrupt context, and
	 * pte lock(a spinlock) is held, which implies preemption disabled.
	 */
	__mod_lruvec_page_state(page, NR_FILE_MAPPED, -nr);

	if (unlikely(PageMlocked(page)))
		clear_page_mlock(page);
out:
	unlock_page_memcg(page);
}