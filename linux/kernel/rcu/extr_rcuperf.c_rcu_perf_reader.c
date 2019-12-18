#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* readlock ) () ;int /*<<< orphan*/  (* readunlock ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NICE ; 
 int /*<<< orphan*/  VERBOSE_PERFOUT_STRING (char*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_of (long) ; 
 TYPE_1__* cur_ops ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  n_rcu_perf_reader_started ; 
 long nr_cpu_ids ; 
 int /*<<< orphan*/  rcu_perf_wait_shutdown () ; 
 int /*<<< orphan*/  set_cpus_allowed_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  torture_kthread_stopping (char*) ; 
 int /*<<< orphan*/  torture_must_stop () ; 

__attribute__((used)) static int
rcu_perf_reader(void *arg)
{
	unsigned long flags;
	int idx;
	long me = (long)arg;

	VERBOSE_PERFOUT_STRING("rcu_perf_reader task started");
	set_cpus_allowed_ptr(current, cpumask_of(me % nr_cpu_ids));
	set_user_nice(current, MAX_NICE);
	atomic_inc(&n_rcu_perf_reader_started);

	do {
		local_irq_save(flags);
		idx = cur_ops->readlock();
		cur_ops->readunlock(idx);
		local_irq_restore(flags);
		rcu_perf_wait_shutdown();
	} while (!torture_must_stop());
	torture_kthread_stopping("rcu_perf_reader");
	return 0;
}