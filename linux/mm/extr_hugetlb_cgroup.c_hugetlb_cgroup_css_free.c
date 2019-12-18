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
struct hugetlb_cgroup {int dummy; } ;
struct cgroup_subsys_state {int dummy; } ;

/* Variables and functions */
 struct hugetlb_cgroup* hugetlb_cgroup_from_css (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  kfree (struct hugetlb_cgroup*) ; 

__attribute__((used)) static void hugetlb_cgroup_css_free(struct cgroup_subsys_state *css)
{
	struct hugetlb_cgroup *h_cgroup;

	h_cgroup = hugetlb_cgroup_from_css(css);
	kfree(h_cgroup);
}