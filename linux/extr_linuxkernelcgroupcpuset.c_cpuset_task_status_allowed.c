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
struct task_struct {int /*<<< orphan*/  mems_allowed; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nodemask_pr_args (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

void cpuset_task_status_allowed(struct seq_file *m, struct task_struct *task)
{
	seq_printf(m, "Mems_allowed:\t%*pb\n",
		   nodemask_pr_args(&task->mems_allowed));
	seq_printf(m, "Mems_allowed_list:\t%*pbl\n",
		   nodemask_pr_args(&task->mems_allowed));
}