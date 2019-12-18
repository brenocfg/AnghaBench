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
struct rcu_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  call_rcu (struct rcu_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_rcu_head_on_stack (struct rcu_head*) ; 
 int /*<<< orphan*/  init_rcu_head_on_stack (struct rcu_head*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  pr_alert (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rcu_torture_err_cb ; 
 int /*<<< orphan*/  rcu_torture_leak_cb ; 

__attribute__((used)) static void rcu_test_debug_objects(void)
{
#ifdef CONFIG_DEBUG_OBJECTS_RCU_HEAD
	struct rcu_head rh1;
	struct rcu_head rh2;

	init_rcu_head_on_stack(&rh1);
	init_rcu_head_on_stack(&rh2);
	pr_alert("%s: WARN: Duplicate call_rcu() test starting.\n", KBUILD_MODNAME);

	/* Try to queue the rh2 pair of callbacks for the same grace period. */
	preempt_disable(); /* Prevent preemption from interrupting test. */
	rcu_read_lock(); /* Make it impossible to finish a grace period. */
	call_rcu(&rh1, rcu_torture_leak_cb); /* Start grace period. */
	local_irq_disable(); /* Make it harder to start a new grace period. */
	call_rcu(&rh2, rcu_torture_leak_cb);
	call_rcu(&rh2, rcu_torture_err_cb); /* Duplicate callback. */
	local_irq_enable();
	rcu_read_unlock();
	preempt_enable();

	/* Wait for them all to get done so we can safely return. */
	rcu_barrier();
	pr_alert("%s: WARN: Duplicate call_rcu() test complete.\n", KBUILD_MODNAME);
	destroy_rcu_head_on_stack(&rh1);
	destroy_rcu_head_on_stack(&rh2);
#else /* #ifdef CONFIG_DEBUG_OBJECTS_RCU_HEAD */
	pr_alert("%s: !CONFIG_DEBUG_OBJECTS_RCU_HEAD, not testing duplicate call_rcu()\n", KBUILD_MODNAME);
#endif /* #else #ifdef CONFIG_DEBUG_OBJECTS_RCU_HEAD */
}