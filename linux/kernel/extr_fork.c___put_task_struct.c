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
struct task_struct {int /*<<< orphan*/  signal; int /*<<< orphan*/  usage; int /*<<< orphan*/  exit_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cgroup_free (struct task_struct*) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  delayacct_tsk_free (struct task_struct*) ; 
 int /*<<< orphan*/  exit_creds (struct task_struct*) ; 
 int /*<<< orphan*/  free_task (struct task_struct*) ; 
 int /*<<< orphan*/  profile_handoff_task (struct task_struct*) ; 
 int /*<<< orphan*/  put_signal_struct (int /*<<< orphan*/ ) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  security_task_free (struct task_struct*) ; 
 int /*<<< orphan*/  task_numa_free (struct task_struct*,int) ; 

void __put_task_struct(struct task_struct *tsk)
{
	WARN_ON(!tsk->exit_state);
	WARN_ON(refcount_read(&tsk->usage));
	WARN_ON(tsk == current);

	cgroup_free(tsk);
	task_numa_free(tsk, true);
	security_task_free(tsk);
	exit_creds(tsk);
	delayacct_tsk_free(tsk);
	put_signal_struct(tsk->signal);

	if (!profile_handoff_task(tsk))
		free_task(tsk);
}