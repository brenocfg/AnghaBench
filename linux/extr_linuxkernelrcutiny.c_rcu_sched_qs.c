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

/* Variables and functions */
 int /*<<< orphan*/  RCU_SOFTIRQ ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  raise_softirq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_bh_ctrlblk ; 
 scalar_t__ rcu_qsctr_help (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_sched_ctrlblk ; 

void rcu_sched_qs(void)
{
	unsigned long flags;

	local_irq_save(flags);
	if (rcu_qsctr_help(&rcu_sched_ctrlblk) +
	    rcu_qsctr_help(&rcu_bh_ctrlblk))
		raise_softirq(RCU_SOFTIRQ);
	local_irq_restore(flags);
}