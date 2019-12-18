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
struct sched_param {int /*<<< orphan*/  sched_priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kthread_prio ; 
 int /*<<< orphan*/  sched_setscheduler_nocheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 

__attribute__((used)) static void rcu_cpu_kthread_setup(unsigned int cpu)
{
#ifdef CONFIG_RCU_BOOST
	struct sched_param sp;

	sp.sched_priority = kthread_prio;
	sched_setscheduler_nocheck(current, SCHED_FIFO, &sp);
#endif /* #ifdef CONFIG_RCU_BOOST */
}