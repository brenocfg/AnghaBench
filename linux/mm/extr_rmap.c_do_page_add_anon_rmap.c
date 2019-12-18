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
struct page {int /*<<< orphan*/  _mapcount; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  NR_ANON_MAPPED ; 
 int /*<<< orphan*/  NR_ANON_THPS ; 
 int /*<<< orphan*/  PageKsm (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageTransHuge (struct page*) ; 
 int RMAP_COMPOUND ; 
 int RMAP_EXCLUSIVE ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  __inc_node_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mod_node_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __page_check_anon_rmap (struct page*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  __page_set_anon_rmap (struct page*,struct vm_area_struct*,unsigned long,int) ; 
 int atomic_inc_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * compound_mapcount_ptr (struct page*) ; 
 int hpage_nr_pages (struct page*) ; 
 int /*<<< orphan*/  page_pgdat (struct page*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void do_page_add_anon_rmap(struct page *page,
	struct vm_area_struct *vma, unsigned long address, int flags)
{
	bool compound = flags & RMAP_COMPOUND;
	bool first;

	if (compound) {
		atomic_t *mapcount;
		VM_BUG_ON_PAGE(!PageLocked(page), page);
		VM_BUG_ON_PAGE(!PageTransHuge(page), page);
		mapcount = compound_mapcount_ptr(page);
		first = atomic_inc_and_test(mapcount);
	} else {
		first = atomic_inc_and_test(&page->_mapcount);
	}

	if (first) {
		int nr = compound ? hpage_nr_pages(page) : 1;
		/*
		 * We use the irq-unsafe __{inc|mod}_zone_page_stat because
		 * these counters are not modified in interrupt context, and
		 * pte lock(a spinlock) is held, which implies preemption
		 * disabled.
		 */
		if (compound)
			__inc_node_page_state(page, NR_ANON_THPS);
		__mod_node_page_state(page_pgdat(page), NR_ANON_MAPPED, nr);
	}
	if (unlikely(PageKsm(page)))
		return;

	VM_BUG_ON_PAGE(!PageLocked(page), page);

	/* address might be in next vma when migration races vma_adjust */
	if (first)
		__page_set_anon_rmap(page, vma, address,
				flags & RMAP_EXCLUSIVE);
	else
		__page_check_anon_rmap(page, vma, address);
}