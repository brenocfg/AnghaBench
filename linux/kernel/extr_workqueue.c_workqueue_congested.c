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
struct workqueue_struct {int flags; int /*<<< orphan*/  cpu_pwqs; } ;
struct pool_workqueue {int /*<<< orphan*/  delayed_works; } ;

/* Variables and functions */
 int WORK_CPU_UNBOUND ; 
 int WQ_UNBOUND ; 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct pool_workqueue* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int smp_processor_id () ; 
 struct pool_workqueue* unbound_pwq_by_node (struct workqueue_struct*,int /*<<< orphan*/ ) ; 

bool workqueue_congested(int cpu, struct workqueue_struct *wq)
{
	struct pool_workqueue *pwq;
	bool ret;

	rcu_read_lock();
	preempt_disable();

	if (cpu == WORK_CPU_UNBOUND)
		cpu = smp_processor_id();

	if (!(wq->flags & WQ_UNBOUND))
		pwq = per_cpu_ptr(wq->cpu_pwqs, cpu);
	else
		pwq = unbound_pwq_by_node(wq, cpu_to_node(cpu));

	ret = !list_empty(&pwq->delayed_works);
	preempt_enable();
	rcu_read_unlock();

	return ret;
}