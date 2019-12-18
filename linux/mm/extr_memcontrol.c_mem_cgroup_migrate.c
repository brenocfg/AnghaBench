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
struct page {struct mem_cgroup* mem_cgroup; } ;
struct mem_cgroup {int /*<<< orphan*/  css; int /*<<< orphan*/  memsw; int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  commit_charge (struct page*,struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  css_get_many (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ do_memsw_account () ; 
 int hpage_nr_pages (struct page*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mem_cgroup_charge_statistics (struct mem_cgroup*,struct page*,int,unsigned int) ; 
 scalar_t__ mem_cgroup_disabled () ; 
 int /*<<< orphan*/  memcg_check_events (struct mem_cgroup*,struct page*) ; 
 int /*<<< orphan*/  page_counter_charge (int /*<<< orphan*/ *,unsigned int) ; 

void mem_cgroup_migrate(struct page *oldpage, struct page *newpage)
{
	struct mem_cgroup *memcg;
	unsigned int nr_pages;
	bool compound;
	unsigned long flags;

	VM_BUG_ON_PAGE(!PageLocked(oldpage), oldpage);
	VM_BUG_ON_PAGE(!PageLocked(newpage), newpage);
	VM_BUG_ON_PAGE(PageAnon(oldpage) != PageAnon(newpage), newpage);
	VM_BUG_ON_PAGE(PageTransHuge(oldpage) != PageTransHuge(newpage),
		       newpage);

	if (mem_cgroup_disabled())
		return;

	/* Page cache replacement: new page already charged? */
	if (newpage->mem_cgroup)
		return;

	/* Swapcache readahead pages can get replaced before being charged */
	memcg = oldpage->mem_cgroup;
	if (!memcg)
		return;

	/* Force-charge the new page. The old one will be freed soon */
	compound = PageTransHuge(newpage);
	nr_pages = compound ? hpage_nr_pages(newpage) : 1;

	page_counter_charge(&memcg->memory, nr_pages);
	if (do_memsw_account())
		page_counter_charge(&memcg->memsw, nr_pages);
	css_get_many(&memcg->css, nr_pages);

	commit_charge(newpage, memcg, false);

	local_irq_save(flags);
	mem_cgroup_charge_statistics(memcg, newpage, compound, nr_pages);
	memcg_check_events(memcg, newpage);
	local_irq_restore(flags);
}