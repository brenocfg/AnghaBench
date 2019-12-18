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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 scalar_t__ CPUCLOCK_MAX ; 
 int /*<<< orphan*/  CPUCLOCK_PERTHREAD (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  CPUCLOCK_PID (int /*<<< orphan*/  const) ; 
 scalar_t__ CPUCLOCK_WHICH (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 struct task_struct* lookup_task (int /*<<< orphan*/  const,int const,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct task_struct *__get_task_for_clock(const clockid_t clock,
						bool getref, bool gettime)
{
	const bool thread = !!CPUCLOCK_PERTHREAD(clock);
	const pid_t pid = CPUCLOCK_PID(clock);
	struct task_struct *p;

	if (CPUCLOCK_WHICH(clock) >= CPUCLOCK_MAX)
		return NULL;

	rcu_read_lock();
	p = lookup_task(pid, thread, gettime);
	if (p && getref)
		get_task_struct(p);
	rcu_read_unlock();
	return p;
}