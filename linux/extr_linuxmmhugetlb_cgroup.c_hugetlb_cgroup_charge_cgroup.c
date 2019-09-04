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
struct hugetlb_cgroup {int /*<<< orphan*/  css; int /*<<< orphan*/ * hugepage; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ HUGETLB_CGROUP_MIN_ORDER ; 
 int /*<<< orphan*/  css_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  css_tryget_online (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/ * hstates ; 
 scalar_t__ huge_page_order (int /*<<< orphan*/ *) ; 
 scalar_t__ hugetlb_cgroup_disabled () ; 
 struct hugetlb_cgroup* hugetlb_cgroup_from_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_counter_try_charge (int /*<<< orphan*/ *,unsigned long,struct page_counter**) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int hugetlb_cgroup_charge_cgroup(int idx, unsigned long nr_pages,
				 struct hugetlb_cgroup **ptr)
{
	int ret = 0;
	struct page_counter *counter;
	struct hugetlb_cgroup *h_cg = NULL;

	if (hugetlb_cgroup_disabled())
		goto done;
	/*
	 * We don't charge any cgroup if the compound page have less
	 * than 3 pages.
	 */
	if (huge_page_order(&hstates[idx]) < HUGETLB_CGROUP_MIN_ORDER)
		goto done;
again:
	rcu_read_lock();
	h_cg = hugetlb_cgroup_from_task(current);
	if (!css_tryget_online(&h_cg->css)) {
		rcu_read_unlock();
		goto again;
	}
	rcu_read_unlock();

	if (!page_counter_try_charge(&h_cg->hugepage[idx], nr_pages, &counter))
		ret = -ENOMEM;
	css_put(&h_cg->css);
done:
	*ptr = h_cg;
	return ret;
}