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
struct task_struct {int dummy; } ;
struct mem_cgroup {int /*<<< orphan*/  css; scalar_t__ oom_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_subsys_on_dfl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  css_get (int /*<<< orphan*/ *) ; 
 struct mem_cgroup* mem_cgroup_from_task (struct task_struct*) ; 
 int /*<<< orphan*/  memory_cgrp_subsys ; 
 struct mem_cgroup* parent_mem_cgroup (struct mem_cgroup*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct mem_cgroup* root_mem_cgroup ; 

struct mem_cgroup *mem_cgroup_get_oom_group(struct task_struct *victim,
					    struct mem_cgroup *oom_domain)
{
	struct mem_cgroup *oom_group = NULL;
	struct mem_cgroup *memcg;

	if (!cgroup_subsys_on_dfl(memory_cgrp_subsys))
		return NULL;

	if (!oom_domain)
		oom_domain = root_mem_cgroup;

	rcu_read_lock();

	memcg = mem_cgroup_from_task(victim);
	if (memcg == root_mem_cgroup)
		goto out;

	/*
	 * Traverse the memory cgroup hierarchy from the victim task's
	 * cgroup up to the OOMing cgroup (or root) to find the
	 * highest-level memory cgroup with oom.group set.
	 */
	for (; memcg; memcg = parent_mem_cgroup(memcg)) {
		if (memcg->oom_group)
			oom_group = memcg;

		if (memcg == oom_domain)
			break;
	}

	if (oom_group)
		css_get(&oom_group->css);
out:
	rcu_read_unlock();

	return oom_group;
}