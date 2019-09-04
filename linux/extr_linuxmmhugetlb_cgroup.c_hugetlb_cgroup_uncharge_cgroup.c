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
struct hugetlb_cgroup {int /*<<< orphan*/ * hugepage; } ;

/* Variables and functions */
 scalar_t__ HUGETLB_CGROUP_MIN_ORDER ; 
 int /*<<< orphan*/ * hstates ; 
 scalar_t__ huge_page_order (int /*<<< orphan*/ *) ; 
 scalar_t__ hugetlb_cgroup_disabled () ; 
 int /*<<< orphan*/  page_counter_uncharge (int /*<<< orphan*/ *,unsigned long) ; 

void hugetlb_cgroup_uncharge_cgroup(int idx, unsigned long nr_pages,
				    struct hugetlb_cgroup *h_cg)
{
	if (hugetlb_cgroup_disabled() || !h_cg)
		return;

	if (huge_page_order(&hstates[idx]) < HUGETLB_CGROUP_MIN_ORDER)
		return;

	page_counter_uncharge(&h_cg->hugepage[idx], nr_pages);
	return;
}