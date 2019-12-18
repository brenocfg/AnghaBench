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
struct rcu_data {scalar_t__ dynticks_nmi_nesting; int dynticks_nesting; int /*<<< orphan*/  dynticks; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_RCU_EQS_DEBUG ; 
 scalar_t__ DYNTICK_IRQ_NONIDLE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPS (char*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  do_nocb_deferred_wakeup (struct rcu_data*) ; 
 int /*<<< orphan*/  is_idle_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_irqs_disabled () ; 
 int /*<<< orphan*/  rcu_data ; 
 int /*<<< orphan*/  rcu_dynticks_eqs_enter () ; 
 int /*<<< orphan*/  rcu_dynticks_task_enter () ; 
 int /*<<< orphan*/  rcu_preempt_deferred_qs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_prepare_for_idle () ; 
 struct rcu_data* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rcu_dyntick (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcu_eqs_enter(bool user)
{
	struct rcu_data *rdp = this_cpu_ptr(&rcu_data);

	WARN_ON_ONCE(rdp->dynticks_nmi_nesting != DYNTICK_IRQ_NONIDLE);
	WRITE_ONCE(rdp->dynticks_nmi_nesting, 0);
	WARN_ON_ONCE(IS_ENABLED(CONFIG_RCU_EQS_DEBUG) &&
		     rdp->dynticks_nesting == 0);
	if (rdp->dynticks_nesting != 1) {
		rdp->dynticks_nesting--;
		return;
	}

	lockdep_assert_irqs_disabled();
	trace_rcu_dyntick(TPS("Start"), rdp->dynticks_nesting, 0, rdp->dynticks);
	WARN_ON_ONCE(IS_ENABLED(CONFIG_RCU_EQS_DEBUG) && !user && !is_idle_task(current));
	rdp = this_cpu_ptr(&rcu_data);
	do_nocb_deferred_wakeup(rdp);
	rcu_prepare_for_idle();
	rcu_preempt_deferred_qs(current);
	WRITE_ONCE(rdp->dynticks_nesting, 0); /* Avoid irq-access tearing. */
	rcu_dynticks_eqs_enter();
	rcu_dynticks_task_enter();
}