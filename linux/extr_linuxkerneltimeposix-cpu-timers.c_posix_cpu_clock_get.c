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
struct timespec64 {int dummy; } ;
struct task_struct {int dummy; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 scalar_t__ CPUCLOCK_PID (int /*<<< orphan*/  const) ; 
 int EINVAL ; 
 struct task_struct* current ; 
 struct task_struct* find_task_by_vpid (scalar_t__ const) ; 
 int posix_cpu_clock_get_task (struct task_struct*,int /*<<< orphan*/  const,struct timespec64*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int posix_cpu_clock_get(const clockid_t which_clock, struct timespec64 *tp)
{
	const pid_t pid = CPUCLOCK_PID(which_clock);
	int err = -EINVAL;

	if (pid == 0) {
		/*
		 * Special case constant value for our own clocks.
		 * We don't have to do any lookup to find ourselves.
		 */
		err = posix_cpu_clock_get_task(current, which_clock, tp);
	} else {
		/*
		 * Find the given PID, and validate that the caller
		 * should be able to see it.
		 */
		struct task_struct *p;
		rcu_read_lock();
		p = find_task_by_vpid(pid);
		if (p)
			err = posix_cpu_clock_get_task(p, which_clock, tp);
		rcu_read_unlock();
	}

	return err;
}