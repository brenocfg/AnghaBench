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
struct cgroup_subsys_state {int dummy; } ;
struct cpuset {int relax_domain_level; struct cgroup_subsys_state css; int /*<<< orphan*/  fmeter; int /*<<< orphan*/  effective_mems; int /*<<< orphan*/  mems_allowed; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {struct cgroup_subsys_state css; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SCHED_LOAD_BALANCE ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct cgroup_subsys_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ alloc_cpumasks (struct cpuset*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmeter_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cpuset*) ; 
 struct cpuset* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodes_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ top_cpuset ; 

__attribute__((used)) static struct cgroup_subsys_state *
cpuset_css_alloc(struct cgroup_subsys_state *parent_css)
{
	struct cpuset *cs;

	if (!parent_css)
		return &top_cpuset.css;

	cs = kzalloc(sizeof(*cs), GFP_KERNEL);
	if (!cs)
		return ERR_PTR(-ENOMEM);

	if (alloc_cpumasks(cs, NULL)) {
		kfree(cs);
		return ERR_PTR(-ENOMEM);
	}

	set_bit(CS_SCHED_LOAD_BALANCE, &cs->flags);
	nodes_clear(cs->mems_allowed);
	nodes_clear(cs->effective_mems);
	fmeter_init(&cs->fmeter);
	cs->relax_domain_level = -1;

	return &cs->css;
}