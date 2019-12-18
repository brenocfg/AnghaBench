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
struct rcu_data {int /*<<< orphan*/  last_fqs_resched; int /*<<< orphan*/  softirq_snap; scalar_t__ ticks_this_gp; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_SOFTIRQ ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kstat_softirqs_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void zero_cpu_stall_ticks(struct rcu_data *rdp)
{
	rdp->ticks_this_gp = 0;
	rdp->softirq_snap = kstat_softirqs_cpu(RCU_SOFTIRQ, smp_processor_id());
	WRITE_ONCE(rdp->last_fqs_resched, jiffies);
}