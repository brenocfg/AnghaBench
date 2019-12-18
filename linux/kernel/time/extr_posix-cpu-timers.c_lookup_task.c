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
struct task_struct {struct task_struct* group_leader; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 struct task_struct* current ; 
 struct task_struct* find_task_by_vpid (int /*<<< orphan*/  const) ; 
 scalar_t__ has_group_leader_pid (struct task_struct*) ; 
 scalar_t__ same_thread_group (struct task_struct*,struct task_struct*) ; 
 scalar_t__ thread_group_leader (struct task_struct*) ; 

__attribute__((used)) static struct task_struct *lookup_task(const pid_t pid, bool thread,
				       bool gettime)
{
	struct task_struct *p;

	/*
	 * If the encoded PID is 0, then the timer is targeted at current
	 * or the process to which current belongs.
	 */
	if (!pid)
		return thread ? current : current->group_leader;

	p = find_task_by_vpid(pid);
	if (!p)
		return p;

	if (thread)
		return same_thread_group(p, current) ? p : NULL;

	if (gettime) {
		/*
		 * For clock_gettime(PROCESS) the task does not need to be
		 * the actual group leader. tsk->sighand gives
		 * access to the group's clock.
		 *
		 * Timers need the group leader because they take a
		 * reference on it and store the task pointer until the
		 * timer is destroyed.
		 */
		return (p == current || thread_group_leader(p)) ? p : NULL;
	}

	/*
	 * For processes require that p is group leader.
	 */
	return has_group_leader_pid(p) ? p : NULL;
}