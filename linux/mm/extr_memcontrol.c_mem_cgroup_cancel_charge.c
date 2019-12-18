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
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_charge (struct mem_cgroup*,unsigned int) ; 
 int hpage_nr_pages (struct page*) ; 
 scalar_t__ mem_cgroup_disabled () ; 

void mem_cgroup_cancel_charge(struct page *page, struct mem_cgroup *memcg,
		bool compound)
{
	unsigned int nr_pages = compound ? hpage_nr_pages(page) : 1;

	if (mem_cgroup_disabled())
		return;
	/*
	 * Swap faults will attempt to charge the same page multiple
	 * times.  But reuse_swap_page() might have removed the page
	 * from swapcache already, so we can't check PageSwapCache().
	 */
	if (!memcg)
		return;

	cancel_charge(memcg, nr_pages);
}