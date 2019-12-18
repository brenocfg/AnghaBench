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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cgroup; } ;
struct mem_cgroup {TYPE_1__ css; } ;

/* Variables and functions */
 int /*<<< orphan*/  memory_cgrp_id ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  pr_cont_cgroup_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  task_cgroup (struct task_struct*,int /*<<< orphan*/ ) ; 

void mem_cgroup_print_oom_context(struct mem_cgroup *memcg, struct task_struct *p)
{
	rcu_read_lock();

	if (memcg) {
		pr_cont(",oom_memcg=");
		pr_cont_cgroup_path(memcg->css.cgroup);
	} else
		pr_cont(",global_oom");
	if (p) {
		pr_cont(",task_memcg=");
		pr_cont_cgroup_path(task_cgroup(p, memory_cgrp_id));
	}
	rcu_read_unlock();
}