#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  exp; int /*<<< orphan*/  norm; } ;
struct TYPE_6__ {TYPE_1__ b; int /*<<< orphan*/  s; } ;
struct TYPE_7__ {TYPE_2__ cpu_no_qs; int /*<<< orphan*/  gp_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_LOCKDEP_WARN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TPS (char*) ; 
 int /*<<< orphan*/  __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  preemptible () ; 
 int /*<<< orphan*/  rcu_report_exp_rdp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ rcu_sched_data ; 
 int /*<<< orphan*/  rcu_sched_state ; 
 int /*<<< orphan*/  this_cpu_ptr (TYPE_3__*) ; 
 int /*<<< orphan*/  trace_rcu_grace_period (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rcu_sched_qs(void)
{
	RCU_LOCKDEP_WARN(preemptible(), "rcu_sched_qs() invoked with preemption enabled!!!");
	if (!__this_cpu_read(rcu_sched_data.cpu_no_qs.s))
		return;
	trace_rcu_grace_period(TPS("rcu_sched"),
			       __this_cpu_read(rcu_sched_data.gp_seq),
			       TPS("cpuqs"));
	__this_cpu_write(rcu_sched_data.cpu_no_qs.b.norm, false);
	if (!__this_cpu_read(rcu_sched_data.cpu_no_qs.b.exp))
		return;
	__this_cpu_write(rcu_sched_data.cpu_no_qs.b.exp, false);
	rcu_report_exp_rdp(&rcu_sched_state,
			   this_cpu_ptr(&rcu_sched_data), true);
}