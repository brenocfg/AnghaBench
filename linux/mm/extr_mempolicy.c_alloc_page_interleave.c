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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  NUMA_INTERLEAVE_HIT ; 
 struct page* __alloc_pages (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  __inc_numa_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int page_to_nid (struct page*) ; 
 int /*<<< orphan*/  page_zone (struct page*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  static_branch_likely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_numa_stat_key ; 

__attribute__((used)) static struct page *alloc_page_interleave(gfp_t gfp, unsigned order,
					unsigned nid)
{
	struct page *page;

	page = __alloc_pages(gfp, order, nid);
	/* skip NUMA_INTERLEAVE_HIT counter update if numa stats is disabled */
	if (!static_branch_likely(&vm_numa_stat_key))
		return page;
	if (page && page_to_nid(page) == nid) {
		preempt_disable();
		__inc_numa_state(page_zone(page), NUMA_INTERLEAVE_HIT);
		preempt_enable();
	}
	return page;
}