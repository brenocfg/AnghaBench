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
struct hugetlb_cgroup {int /*<<< orphan*/ * hugepage; } ;

/* Variables and functions */
 scalar_t__ hugetlb_cgroup_disabled () ; 
 struct hugetlb_cgroup* hugetlb_cgroup_from_page (struct page*) ; 
 int /*<<< orphan*/  hugetlb_lock ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_counter_uncharge (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_hugetlb_cgroup (struct page*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void hugetlb_cgroup_uncharge_page(int idx, unsigned long nr_pages,
				  struct page *page)
{
	struct hugetlb_cgroup *h_cg;

	if (hugetlb_cgroup_disabled())
		return;
	lockdep_assert_held(&hugetlb_lock);
	h_cg = hugetlb_cgroup_from_page(page);
	if (unlikely(!h_cg))
		return;
	set_hugetlb_cgroup(page, NULL);
	page_counter_uncharge(&h_cg->hugepage[idx], nr_pages);
	return;
}