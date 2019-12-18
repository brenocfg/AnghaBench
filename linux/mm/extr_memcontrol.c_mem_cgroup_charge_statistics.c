#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct mem_cgroup {TYPE_1__* vmstats_percpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_page_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCG_CACHE ; 
 int /*<<< orphan*/  MEMCG_RSS ; 
 int /*<<< orphan*/  MEMCG_RSS_HUGE ; 
 int /*<<< orphan*/  NR_SHMEM ; 
 int /*<<< orphan*/  PGPGIN ; 
 int /*<<< orphan*/  PGPGOUT ; 
 scalar_t__ PageAnon (struct page*) ; 
 scalar_t__ PageSwapBacked (struct page*) ; 
 int /*<<< orphan*/  PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  __count_memcg_events (struct mem_cgroup*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __mod_memcg_state (struct mem_cgroup*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __this_cpu_add (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mem_cgroup_charge_statistics(struct mem_cgroup *memcg,
					 struct page *page,
					 bool compound, int nr_pages)
{
	/*
	 * Here, RSS means 'mapped anon' and anon's SwapCache. Shmem/tmpfs is
	 * counted as CACHE even if it's on ANON LRU.
	 */
	if (PageAnon(page))
		__mod_memcg_state(memcg, MEMCG_RSS, nr_pages);
	else {
		__mod_memcg_state(memcg, MEMCG_CACHE, nr_pages);
		if (PageSwapBacked(page))
			__mod_memcg_state(memcg, NR_SHMEM, nr_pages);
	}

	if (compound) {
		VM_BUG_ON_PAGE(!PageTransHuge(page), page);
		__mod_memcg_state(memcg, MEMCG_RSS_HUGE, nr_pages);
	}

	/* pagein of a big page is an event. So, ignore page size */
	if (nr_pages > 0)
		__count_memcg_events(memcg, PGPGIN, 1);
	else {
		__count_memcg_events(memcg, PGPGOUT, 1);
		nr_pages = -nr_pages; /* for event */
	}

	__this_cpu_add(memcg->vmstats_percpu->nr_page_events, nr_pages);
}