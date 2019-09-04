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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct hugetlb_cgroup {TYPE_1__ css; } ;

/* Variables and functions */
 struct hugetlb_cgroup* hugetlb_cgroup_from_css (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct hugetlb_cgroup *
parent_hugetlb_cgroup(struct hugetlb_cgroup *h_cg)
{
	return hugetlb_cgroup_from_css(h_cg->css.parent);
}