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
 int hugetlb_max_hstate ; 
 scalar_t__ page_counter_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool hugetlb_cgroup_have_usage(struct hugetlb_cgroup *h_cg)
{
	int idx;

	for (idx = 0; idx < hugetlb_max_hstate; idx++) {
		if (page_counter_read(&h_cg->hugepage[idx]))
			return true;
	}
	return false;
}