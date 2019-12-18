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
struct cpuset {int use_parent_ecpus; int /*<<< orphan*/  flags; int /*<<< orphan*/  child_ecpus_count; } ;
struct cgroup_subsys_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ONLINE ; 
 int /*<<< orphan*/  CS_SCHED_LOAD_BALANCE ; 
 int /*<<< orphan*/  cgroup_subsys_on_dfl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuset_cgrp_subsys ; 
 int /*<<< orphan*/  cpuset_dec () ; 
 int /*<<< orphan*/  cpuset_rwsem ; 
 struct cpuset* css_cs (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 scalar_t__ is_partition_root (struct cpuset*) ; 
 scalar_t__ is_sched_load_balance (struct cpuset*) ; 
 struct cpuset* parent_cs (struct cpuset*) ; 
 int /*<<< orphan*/  percpu_down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  update_flag (int /*<<< orphan*/ ,struct cpuset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_prstate (struct cpuset*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpuset_css_offline(struct cgroup_subsys_state *css)
{
	struct cpuset *cs = css_cs(css);

	get_online_cpus();
	percpu_down_write(&cpuset_rwsem);

	if (is_partition_root(cs))
		update_prstate(cs, 0);

	if (!cgroup_subsys_on_dfl(cpuset_cgrp_subsys) &&
	    is_sched_load_balance(cs))
		update_flag(CS_SCHED_LOAD_BALANCE, cs, 0);

	if (cs->use_parent_ecpus) {
		struct cpuset *parent = parent_cs(cs);

		cs->use_parent_ecpus = false;
		parent->child_ecpus_count--;
	}

	cpuset_dec();
	clear_bit(CS_ONLINE, &cs->flags);

	percpu_up_write(&cpuset_rwsem);
	put_online_cpus();
}