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
struct task_struct {struct task_struct* group_leader; } ;
struct TYPE_3__ {struct task_struct* task; int /*<<< orphan*/  entry; } ;
struct TYPE_4__ {TYPE_1__ cpu; } ;
struct k_itimer {TYPE_2__ it; int /*<<< orphan*/  it_clock; int /*<<< orphan*/ * kclock; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ CPUCLOCK_MAX ; 
 scalar_t__ CPUCLOCK_PERTHREAD (int /*<<< orphan*/ ) ; 
 scalar_t__ CPUCLOCK_PID (int /*<<< orphan*/ ) ; 
 scalar_t__ CPUCLOCK_WHICH (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_posix_cpu ; 
 struct task_struct* current ; 
 struct task_struct* find_task_by_vpid (scalar_t__ const) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  has_group_leader_pid (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  same_thread_group (struct task_struct*,struct task_struct*) ; 

__attribute__((used)) static int posix_cpu_timer_create(struct k_itimer *new_timer)
{
	int ret = 0;
	const pid_t pid = CPUCLOCK_PID(new_timer->it_clock);
	struct task_struct *p;

	if (CPUCLOCK_WHICH(new_timer->it_clock) >= CPUCLOCK_MAX)
		return -EINVAL;

	new_timer->kclock = &clock_posix_cpu;

	INIT_LIST_HEAD(&new_timer->it.cpu.entry);

	rcu_read_lock();
	if (CPUCLOCK_PERTHREAD(new_timer->it_clock)) {
		if (pid == 0) {
			p = current;
		} else {
			p = find_task_by_vpid(pid);
			if (p && !same_thread_group(p, current))
				p = NULL;
		}
	} else {
		if (pid == 0) {
			p = current->group_leader;
		} else {
			p = find_task_by_vpid(pid);
			if (p && !has_group_leader_pid(p))
				p = NULL;
		}
	}
	new_timer->it.cpu.task = p;
	if (p) {
		get_task_struct(p);
	} else {
		ret = -EINVAL;
	}
	rcu_read_unlock();

	return ret;
}