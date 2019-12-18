#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct page {int /*<<< orphan*/  mapping; } ;
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 scalar_t__ PageLRU (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  commit_charge (struct page*,struct mem_cgroup*,int) ; 
 scalar_t__ do_memsw_account () ; 
 int hpage_nr_pages (struct page*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  mem_cgroup_charge_statistics (struct mem_cgroup*,struct page*,int,unsigned int) ; 
 scalar_t__ mem_cgroup_disabled () ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_swap (TYPE_1__,unsigned int) ; 
 int /*<<< orphan*/  memcg_check_events (struct mem_cgroup*,struct page*) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 

void mem_cgroup_commit_charge(struct page *page, struct mem_cgroup *memcg,
			      bool lrucare, bool compound)
{
	unsigned int nr_pages = compound ? hpage_nr_pages(page) : 1;

	VM_BUG_ON_PAGE(!page->mapping, page);
	VM_BUG_ON_PAGE(PageLRU(page) && !lrucare, page);

	if (mem_cgroup_disabled())
		return;
	/*
	 * Swap faults will attempt to charge the same page multiple
	 * times.  But reuse_swap_page() might have removed the page
	 * from swapcache already, so we can't check PageSwapCache().
	 */
	if (!memcg)
		return;

	commit_charge(page, memcg, lrucare);

	local_irq_disable();
	mem_cgroup_charge_statistics(memcg, page, compound, nr_pages);
	memcg_check_events(memcg, page);
	local_irq_enable();

	if (do_memsw_account() && PageSwapCache(page)) {
		swp_entry_t entry = { .val = page_private(page) };
		/*
		 * The swap entry might not get freed for a long time,
		 * let's not wait for it.  The page already received a
		 * memory+swap charge, drop the swap entry duplicate.
		 */
		mem_cgroup_uncharge_swap(entry, nr_pages);
	}
}