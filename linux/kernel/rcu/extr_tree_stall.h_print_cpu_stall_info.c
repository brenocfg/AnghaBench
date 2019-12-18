#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rcu_data {unsigned long ticks_this_gp; int grpmask; int /*<<< orphan*/  softirq_snap; int /*<<< orphan*/  dynticks_nmi_nesting; int /*<<< orphan*/  dynticks_nesting; scalar_t__ rcu_iw_pending; TYPE_1__* mynode; scalar_t__ rcu_iw_gp_seq; scalar_t__ gp_seq; } ;
struct TYPE_4__ {scalar_t__ n_force_qs_gpstart; int /*<<< orphan*/  n_force_qs; scalar_t__ gp_seq; } ;
struct TYPE_3__ {int qsmaskinit; int qsmaskinitnext; scalar_t__ gp_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_IRQ_WORK ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCU_SOFTIRQ ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_online (int) ; 
 int /*<<< orphan*/  kstat_softirqs_cpu (int /*<<< orphan*/ ,int) ; 
 scalar_t__ min (unsigned long,unsigned long) ; 
 struct rcu_data* per_cpu_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,char,char,char,char,unsigned long,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  print_cpu_stall_fast_no_hz (char*,int) ; 
 int /*<<< orphan*/  rcu_data ; 
 int rcu_dynticks_snap (struct rcu_data*) ; 
 unsigned long rcu_seq_ctr (scalar_t__) ; 
 TYPE_2__ rcu_state ; 
 int /*<<< orphan*/  touch_nmi_watchdog () ; 

__attribute__((used)) static void print_cpu_stall_info(int cpu)
{
	unsigned long delta;
	char fast_no_hz[72];
	struct rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);
	char *ticks_title;
	unsigned long ticks_value;

	/*
	 * We could be printing a lot while holding a spinlock.  Avoid
	 * triggering hard lockup.
	 */
	touch_nmi_watchdog();

	ticks_value = rcu_seq_ctr(rcu_state.gp_seq - rdp->gp_seq);
	if (ticks_value) {
		ticks_title = "GPs behind";
	} else {
		ticks_title = "ticks this GP";
		ticks_value = rdp->ticks_this_gp;
	}
	print_cpu_stall_fast_no_hz(fast_no_hz, cpu);
	delta = rcu_seq_ctr(rdp->mynode->gp_seq - rdp->rcu_iw_gp_seq);
	pr_err("\t%d-%c%c%c%c: (%lu %s) idle=%03x/%ld/%#lx softirq=%u/%u fqs=%ld %s\n",
	       cpu,
	       "O."[!!cpu_online(cpu)],
	       "o."[!!(rdp->grpmask & rdp->mynode->qsmaskinit)],
	       "N."[!!(rdp->grpmask & rdp->mynode->qsmaskinitnext)],
	       !IS_ENABLED(CONFIG_IRQ_WORK) ? '?' :
			rdp->rcu_iw_pending ? (int)min(delta, 9UL) + '0' :
				"!."[!delta],
	       ticks_value, ticks_title,
	       rcu_dynticks_snap(rdp) & 0xfff,
	       rdp->dynticks_nesting, rdp->dynticks_nmi_nesting,
	       rdp->softirq_snap, kstat_softirqs_cpu(RCU_SOFTIRQ, cpu),
	       READ_ONCE(rcu_state.n_force_qs) - rcu_state.n_force_qs_gpstart,
	       fast_no_hz);
}