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
struct rcu_dynticks {scalar_t__ dynticks_nmi_nesting; int /*<<< orphan*/  dynticks; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPS (char*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  rcu_dynticks ; 
 scalar_t__ rcu_dynticks_curr_cpu_in_eqs () ; 
 int /*<<< orphan*/  rcu_dynticks_eqs_exit () ; 
 struct rcu_dynticks* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rcu_dyntick (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

void rcu_nmi_enter(void)
{
	struct rcu_dynticks *rdtp = this_cpu_ptr(&rcu_dynticks);
	long incby = 2;

	/* Complain about underflow. */
	WARN_ON_ONCE(rdtp->dynticks_nmi_nesting < 0);

	/*
	 * If idle from RCU viewpoint, atomically increment ->dynticks
	 * to mark non-idle and increment ->dynticks_nmi_nesting by one.
	 * Otherwise, increment ->dynticks_nmi_nesting by two.  This means
	 * if ->dynticks_nmi_nesting is equal to one, we are guaranteed
	 * to be in the outermost NMI handler that interrupted an RCU-idle
	 * period (observation due to Andy Lutomirski).
	 */
	if (rcu_dynticks_curr_cpu_in_eqs()) {
		rcu_dynticks_eqs_exit();
		incby = 1;
	}
	trace_rcu_dyntick(incby == 1 ? TPS("Endirq") : TPS("++="),
			  rdtp->dynticks_nmi_nesting,
			  rdtp->dynticks_nmi_nesting + incby, rdtp->dynticks);
	WRITE_ONCE(rdtp->dynticks_nmi_nesting, /* Prevent store tearing. */
		   rdtp->dynticks_nmi_nesting + incby);
	barrier();
}