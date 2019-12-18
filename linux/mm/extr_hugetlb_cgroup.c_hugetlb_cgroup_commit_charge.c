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
struct hugetlb_cgroup {int dummy; } ;

/* Variables and functions */
 scalar_t__ hugetlb_cgroup_disabled () ; 
 int /*<<< orphan*/  set_hugetlb_cgroup (struct page*,struct hugetlb_cgroup*) ; 

void hugetlb_cgroup_commit_charge(int idx, unsigned long nr_pages,
				  struct hugetlb_cgroup *h_cg,
				  struct page *page)
{
	if (hugetlb_cgroup_disabled() || !h_cg)
		return;

	set_hugetlb_cgroup(page, h_cg);
	return;
}