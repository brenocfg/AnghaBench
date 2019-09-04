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
struct task_struct {int dummy; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 scalar_t__ CPUCLOCK_MAX ; 
 scalar_t__ CPUCLOCK_PERTHREAD (int /*<<< orphan*/  const) ; 
 scalar_t__ CPUCLOCK_PID (int /*<<< orphan*/  const) ; 
 scalar_t__ CPUCLOCK_WHICH (int /*<<< orphan*/  const) ; 
 int EINVAL ; 
 int /*<<< orphan*/  current ; 
 struct task_struct* find_task_by_vpid (scalar_t__ const) ; 
 int /*<<< orphan*/  has_group_leader_pid (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  same_thread_group (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_clock(const clockid_t which_clock)
{
	int error = 0;
	struct task_struct *p;
	const pid_t pid = CPUCLOCK_PID(which_clock);

	if (CPUCLOCK_WHICH(which_clock) >= CPUCLOCK_MAX)
		return -EINVAL;

	if (pid == 0)
		return 0;

	rcu_read_lock();
	p = find_task_by_vpid(pid);
	if (!p || !(CPUCLOCK_PERTHREAD(which_clock) ?
		   same_thread_group(p, current) : has_group_leader_pid(p))) {
		error = -EINVAL;
	}
	rcu_read_unlock();

	return error;
}