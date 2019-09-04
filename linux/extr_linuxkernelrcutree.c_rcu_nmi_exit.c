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
struct rcu_dynticks {int dynticks_nmi_nesting; int /*<<< orphan*/  dynticks; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPS (char*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int) ; 
 int /*<<< orphan*/  rcu_dynticks ; 
 int rcu_dynticks_curr_cpu_in_eqs () ; 
 int /*<<< orphan*/  rcu_dynticks_eqs_enter () ; 
 struct rcu_dynticks* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rcu_dyntick (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

void rcu_nmi_exit(void)
{
	struct rcu_dynticks *rdtp = this_cpu_ptr(&rcu_dynticks);

	/*
	 * Check for ->dynticks_nmi_nesting underflow and bad ->dynticks.
	 * (We are exiting an NMI handler, so RCU better be paying attention
	 * to us!)
	 */
	WARN_ON_ONCE(rdtp->dynticks_nmi_nesting <= 0);
	WARN_ON_ONCE(rcu_dynticks_curr_cpu_in_eqs());

	/*
	 * If the nesting level is not 1, the CPU wasn't RCU-idle, so
	 * leave it in non-RCU-idle state.
	 */
	if (rdtp->dynticks_nmi_nesting != 1) {
		trace_rcu_dyntick(TPS("--="), rdtp->dynticks_nmi_nesting, rdtp->dynticks_nmi_nesting - 2, rdtp->dynticks);
		WRITE_ONCE(rdtp->dynticks_nmi_nesting, /* No store tearing. */
			   rdtp->dynticks_nmi_nesting - 2);
		return;
	}

	/* This NMI interrupted an RCU-idle CPU, restore RCU-idleness. */
	trace_rcu_dyntick(TPS("Startirq"), rdtp->dynticks_nmi_nesting, 0, rdtp->dynticks);
	WRITE_ONCE(rdtp->dynticks_nmi_nesting, 0); /* Avoid store tearing. */
	rcu_dynticks_eqs_enter();
}