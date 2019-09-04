#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  norm; } ;
struct TYPE_5__ {TYPE_1__ b; int /*<<< orphan*/  s; } ;
struct TYPE_6__ {TYPE_2__ cpu_no_qs; int /*<<< orphan*/  gp_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_LOCKDEP_WARN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TPS (char*) ; 
 scalar_t__ __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  preemptible () ; 
 TYPE_3__ rcu_bh_data ; 
 int /*<<< orphan*/  trace_rcu_grace_period (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void rcu_bh_qs(void)
{
	RCU_LOCKDEP_WARN(preemptible(), "rcu_bh_qs() invoked with preemption enabled!!!");
	if (__this_cpu_read(rcu_bh_data.cpu_no_qs.s)) {
		trace_rcu_grace_period(TPS("rcu_bh"),
				       __this_cpu_read(rcu_bh_data.gp_seq),
				       TPS("cpuqs"));
		__this_cpu_write(rcu_bh_data.cpu_no_qs.b.norm, false);
	}
}