#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sum_sleep_runtime; int /*<<< orphan*/  wait_sum; } ;
struct TYPE_4__ {TYPE_1__ statistics; int /*<<< orphan*/  sum_exec_runtime; int /*<<< orphan*/  vruntime; } ;
struct task_struct {TYPE_2__ se; int /*<<< orphan*/  prio; scalar_t__ nivcsw; scalar_t__ nvcsw; int /*<<< orphan*/  comm; } ;
struct seq_file {int dummy; } ;
struct rq {struct task_struct* curr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  SPLIT_NS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedstat_val_or_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_group (struct task_struct*) ; 
 int /*<<< orphan*/  task_group_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_node (struct task_struct*) ; 
 int /*<<< orphan*/  task_numa_group_id (struct task_struct*) ; 
 int /*<<< orphan*/  task_pid_nr (struct task_struct*) ; 
 int /*<<< orphan*/  task_state_to_char (struct task_struct*) ; 

__attribute__((used)) static void
print_task(struct seq_file *m, struct rq *rq, struct task_struct *p)
{
	if (rq->curr == p)
		SEQ_printf(m, ">R");
	else
		SEQ_printf(m, " %c", task_state_to_char(p));

	SEQ_printf(m, "%15s %5d %9Ld.%06ld %9Ld %5d ",
		p->comm, task_pid_nr(p),
		SPLIT_NS(p->se.vruntime),
		(long long)(p->nvcsw + p->nivcsw),
		p->prio);

	SEQ_printf(m, "%9Ld.%06ld %9Ld.%06ld %9Ld.%06ld",
		SPLIT_NS(schedstat_val_or_zero(p->se.statistics.wait_sum)),
		SPLIT_NS(p->se.sum_exec_runtime),
		SPLIT_NS(schedstat_val_or_zero(p->se.statistics.sum_sleep_runtime)));

#ifdef CONFIG_NUMA_BALANCING
	SEQ_printf(m, " %d %d", task_node(p), task_numa_group_id(p));
#endif
#ifdef CONFIG_CGROUP_SCHED
	SEQ_printf(m, " %s", task_group_path(task_group(p)));
#endif

	SEQ_printf(m, "\n");
}