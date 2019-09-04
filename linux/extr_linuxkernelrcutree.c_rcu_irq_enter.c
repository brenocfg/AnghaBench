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
struct rcu_dynticks {int dynticks_nmi_nesting; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_irqs_disabled () ; 
 int /*<<< orphan*/  rcu_cleanup_after_idle () ; 
 int /*<<< orphan*/  rcu_dynticks ; 
 int /*<<< orphan*/  rcu_dynticks_task_exit () ; 
 int /*<<< orphan*/  rcu_nmi_enter () ; 
 struct rcu_dynticks* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void rcu_irq_enter(void)
{
	struct rcu_dynticks *rdtp = this_cpu_ptr(&rcu_dynticks);

	lockdep_assert_irqs_disabled();
	if (rdtp->dynticks_nmi_nesting == 0)
		rcu_dynticks_task_exit();
	rcu_nmi_enter();
	if (rdtp->dynticks_nmi_nesting == 1)
		rcu_cleanup_after_idle();
}