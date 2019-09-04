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
struct rcu_dynticks {long dynticks_nesting; long dynticks_nmi_nesting; int /*<<< orphan*/  dynticks; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_RCU_EQS_DEBUG ; 
 int DYNTICK_IRQ_NONIDLE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPS (char*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (long,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  is_idle_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_irqs_disabled () ; 
 int /*<<< orphan*/  rcu_cleanup_after_idle () ; 
 int /*<<< orphan*/  rcu_dynticks ; 
 int /*<<< orphan*/  rcu_dynticks_eqs_exit () ; 
 int /*<<< orphan*/  rcu_dynticks_task_exit () ; 
 struct rcu_dynticks* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rcu_dyntick (int /*<<< orphan*/ ,long,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcu_eqs_exit(bool user)
{
	struct rcu_dynticks *rdtp;
	long oldval;

	lockdep_assert_irqs_disabled();
	rdtp = this_cpu_ptr(&rcu_dynticks);
	oldval = rdtp->dynticks_nesting;
	WARN_ON_ONCE(IS_ENABLED(CONFIG_RCU_EQS_DEBUG) && oldval < 0);
	if (oldval) {
		rdtp->dynticks_nesting++;
		return;
	}
	rcu_dynticks_task_exit();
	rcu_dynticks_eqs_exit();
	rcu_cleanup_after_idle();
	trace_rcu_dyntick(TPS("End"), rdtp->dynticks_nesting, 1, rdtp->dynticks);
	WARN_ON_ONCE(IS_ENABLED(CONFIG_RCU_EQS_DEBUG) && !user && !is_idle_task(current));
	WRITE_ONCE(rdtp->dynticks_nesting, 1);
	WRITE_ONCE(rdtp->dynticks_nmi_nesting, DYNTICK_IRQ_NONIDLE);
}