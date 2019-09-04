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
struct task_struct {int /*<<< orphan*/  personality; } ;
struct seq_file {int dummy; } ;
struct pid_namespace {int dummy; } ;
struct pid {int dummy; } ;

/* Variables and functions */
 int lock_trace (struct task_struct*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_trace (struct task_struct*) ; 

__attribute__((used)) static int proc_pid_personality(struct seq_file *m, struct pid_namespace *ns,
				struct pid *pid, struct task_struct *task)
{
	int err = lock_trace(task);
	if (!err) {
		seq_printf(m, "%08x\n", task->personality);
		unlock_trace(task);
	}
	return err;
}