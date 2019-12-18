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
struct rcu_data {int /*<<< orphan*/  dynticks; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_RCU_EQS_DEBUG ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int RCU_DYNTICK_CTRL_CTR ; 
 int RCU_DYNTICK_CTRL_MASK ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_andnot (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_data ; 
 int /*<<< orphan*/  rcu_eqs_special_exit () ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 struct rcu_data* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcu_dynticks_eqs_exit(void)
{
	struct rcu_data *rdp = this_cpu_ptr(&rcu_data);
	int seq;

	/*
	 * CPUs seeing atomic_add_return() must see prior idle sojourns,
	 * and we also must force ordering with the next RCU read-side
	 * critical section.
	 */
	seq = atomic_add_return(RCU_DYNTICK_CTRL_CTR, &rdp->dynticks);
	WARN_ON_ONCE(IS_ENABLED(CONFIG_RCU_EQS_DEBUG) &&
		     !(seq & RCU_DYNTICK_CTRL_CTR));
	if (seq & RCU_DYNTICK_CTRL_MASK) {
		atomic_andnot(RCU_DYNTICK_CTRL_MASK, &rdp->dynticks);
		smp_mb__after_atomic(); /* _exit after clearing mask. */
		/* Prefer duplicate flushes to losing a flush. */
		rcu_eqs_special_exit();
	}
}