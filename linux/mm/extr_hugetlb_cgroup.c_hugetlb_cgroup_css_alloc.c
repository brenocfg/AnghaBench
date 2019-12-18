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
struct cgroup_subsys_state {int dummy; } ;
struct hugetlb_cgroup {struct cgroup_subsys_state css; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct cgroup_subsys_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hugetlb_cgroup* hugetlb_cgroup_from_css (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  hugetlb_cgroup_init (struct hugetlb_cgroup*,struct hugetlb_cgroup*) ; 
 struct hugetlb_cgroup* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct hugetlb_cgroup* root_h_cgroup ; 

__attribute__((used)) static struct cgroup_subsys_state *
hugetlb_cgroup_css_alloc(struct cgroup_subsys_state *parent_css)
{
	struct hugetlb_cgroup *parent_h_cgroup = hugetlb_cgroup_from_css(parent_css);
	struct hugetlb_cgroup *h_cgroup;

	h_cgroup = kzalloc(sizeof(*h_cgroup), GFP_KERNEL);
	if (!h_cgroup)
		return ERR_PTR(-ENOMEM);

	if (!parent_h_cgroup)
		root_h_cgroup = h_cgroup;

	hugetlb_cgroup_init(h_cgroup, parent_h_cgroup);
	return &h_cgroup->css;
}