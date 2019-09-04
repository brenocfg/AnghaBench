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
struct page_counter {int dummy; } ;
struct hugetlb_cgroup {struct page_counter* hugepage; } ;

/* Variables and functions */
 int HUGE_MAX_HSTATE ; 
 int /*<<< orphan*/  PAGE_COUNTER_MAX ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/ * hstates ; 
 int huge_page_order (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_counter_init (struct page_counter*,struct page_counter*) ; 
 int page_counter_set_max (struct page_counter*,unsigned long) ; 
 unsigned long round_down (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hugetlb_cgroup_init(struct hugetlb_cgroup *h_cgroup,
				struct hugetlb_cgroup *parent_h_cgroup)
{
	int idx;

	for (idx = 0; idx < HUGE_MAX_HSTATE; idx++) {
		struct page_counter *counter = &h_cgroup->hugepage[idx];
		struct page_counter *parent = NULL;
		unsigned long limit;
		int ret;

		if (parent_h_cgroup)
			parent = &parent_h_cgroup->hugepage[idx];
		page_counter_init(counter, parent);

		limit = round_down(PAGE_COUNTER_MAX,
				   1 << huge_page_order(&hstates[idx]));
		ret = page_counter_set_max(counter, limit);
		VM_BUG_ON(ret);
	}
}