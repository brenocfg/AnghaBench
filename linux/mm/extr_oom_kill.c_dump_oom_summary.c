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
struct task_struct {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;
struct oom_control {size_t constraint; int /*<<< orphan*/  memcg; int /*<<< orphan*/  nodemask; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuset_print_current_mems_allowed () ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  mem_cgroup_print_oom_context (int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  nodemask_pr_args (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * oom_constraint_text ; 
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_uid (struct task_struct*) ; 

__attribute__((used)) static void dump_oom_summary(struct oom_control *oc, struct task_struct *victim)
{
	/* one line summary of the oom killer context. */
	pr_info("oom-kill:constraint=%s,nodemask=%*pbl",
			oom_constraint_text[oc->constraint],
			nodemask_pr_args(oc->nodemask));
	cpuset_print_current_mems_allowed();
	mem_cgroup_print_oom_context(oc->memcg, victim);
	pr_cont(",task=%s,pid=%d,uid=%d\n", victim->comm, victim->pid,
		from_kuid(&init_user_ns, task_uid(victim)));
}