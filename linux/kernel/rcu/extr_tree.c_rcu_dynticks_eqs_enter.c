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
 int /*<<< orphan*/  rcu_data ; 
 struct rcu_data* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcu_dynticks_eqs_enter(void)
{
	struct rcu_data *rdp = this_cpu_ptr(&rcu_data);
	int seq;

	/*
	 * CPUs seeing atomic_add_return() must see prior RCU read-side
	 * critical sections, and we also must force ordering with the
	 * next idle sojourn.
	 */
	seq = atomic_add_return(RCU_DYNTICK_CTRL_CTR, &rdp->dynticks);
	/* Better be in an extended quiescent state! */
	WARN_ON_ONCE(IS_ENABLED(CONFIG_RCU_EQS_DEBUG) &&
		     (seq & RCU_DYNTICK_CTRL_CTR));
	/* Better not have special action (TLB flush) pending! */
	WARN_ON_ONCE(IS_ENABLED(CONFIG_RCU_EQS_DEBUG) &&
		     (seq & RCU_DYNTICK_CTRL_MASK));
}