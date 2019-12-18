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
 int /*<<< orphan*/  NR_ANON_MAPPED ; 
 int /*<<< orphan*/  PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageMlocked (struct page*) ; 
 scalar_t__ PageTransCompound (struct page*) ; 
 int /*<<< orphan*/  __dec_node_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_negative (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_page_mlock (struct page*) ; 
 int /*<<< orphan*/  compound_head (struct page*) ; 
 int /*<<< orphan*/  deferred_split_huge_page (int /*<<< orphan*/ ) ; 
 void page_remove_anon_compound_rmap (struct page*) ; 
 void page_remove_file_rmap (struct page*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void page_remove_rmap(struct page *page, bool compound)
{
	if (!PageAnon(page))
		return page_remove_file_rmap(page, compound);

	if (compound)
		return page_remove_anon_compound_rmap(page);

	/* page still mapped by someone else? */
	if (!atomic_add_negative(-1, &page->_mapcount))
		return;

	/*
	 * We use the irq-unsafe __{inc|mod}_zone_page_stat because
	 * these counters are not modified in interrupt context, and
	 * pte lock(a spinlock) is held, which implies preemption disabled.
	 */
	__dec_node_page_state(page, NR_ANON_MAPPED);

	if (unlikely(PageMlocked(page)))
		clear_page_mlock(page);

	if (PageTransCompound(page))
		deferred_split_huge_page(compound_head(page));

	/*
	 * It would be tidy to reset the PageAnon mapping here,
	 * but that might overwrite a racing page_add_anon_rmap
	 * which increments mapcount after us but sets mapping
	 * before us: so leave the reset to free_unref_page,
	 * and remember that it's only reliable while mapped.
	 * Leaving it set also helps swapoff to reinstate ptes
	 * faster for those pages still in swapcache.
	 */
}