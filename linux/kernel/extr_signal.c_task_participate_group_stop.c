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
struct task_struct {int jobctl; struct signal_struct* signal; } ;
struct signal_struct {scalar_t__ group_stop_count; int flags; } ;

/* Variables and functions */
 int JOBCTL_STOP_CONSUME ; 
 int JOBCTL_STOP_PENDING ; 
 int SIGNAL_STOP_STOPPED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  signal_set_stop_flags (struct signal_struct*,int) ; 
 int /*<<< orphan*/  task_clear_jobctl_pending (struct task_struct*,int) ; 

__attribute__((used)) static bool task_participate_group_stop(struct task_struct *task)
{
	struct signal_struct *sig = task->signal;
	bool consume = task->jobctl & JOBCTL_STOP_CONSUME;

	WARN_ON_ONCE(!(task->jobctl & JOBCTL_STOP_PENDING));

	task_clear_jobctl_pending(task, JOBCTL_STOP_PENDING);

	if (!consume)
		return false;

	if (!WARN_ON_ONCE(sig->group_stop_count == 0))
		sig->group_stop_count--;

	/*
	 * Tell the caller to notify completion iff we are entering into a
	 * fresh group stop.  Read comment in do_signal_stop() for details.
	 */
	if (!sig->group_stop_count && !(sig->flags & SIGNAL_STOP_STOPPED)) {
		signal_set_stop_flags(sig, SIGNAL_STOP_STOPPED);
		return true;
	}
	return false;
}