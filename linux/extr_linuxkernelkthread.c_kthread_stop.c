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
struct task_struct {int exit_code; } ;
struct kthread {int /*<<< orphan*/  exited; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTHREAD_SHOULD_STOP ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  kthread_unpark (struct task_struct*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct kthread* to_kthread (struct task_struct*) ; 
 int /*<<< orphan*/  trace_sched_kthread_stop (struct task_struct*) ; 
 int /*<<< orphan*/  trace_sched_kthread_stop_ret (int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

int kthread_stop(struct task_struct *k)
{
	struct kthread *kthread;
	int ret;

	trace_sched_kthread_stop(k);

	get_task_struct(k);
	kthread = to_kthread(k);
	set_bit(KTHREAD_SHOULD_STOP, &kthread->flags);
	kthread_unpark(k);
	wake_up_process(k);
	wait_for_completion(&kthread->exited);
	ret = k->exit_code;
	put_task_struct(k);

	trace_sched_kthread_stop_ret(ret);
	return ret;
}