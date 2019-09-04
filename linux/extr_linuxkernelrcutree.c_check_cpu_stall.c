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
struct rcu_state {int /*<<< orphan*/  jiffies_stall; int /*<<< orphan*/  gp_seq; int /*<<< orphan*/  gp_start; } ;
struct rcu_node {int /*<<< orphan*/  qsmask; } ;
struct rcu_data {unsigned long grpmask; struct rcu_node* mynode; } ;

/* Variables and functions */
 unsigned long RCU_STALL_RAT_DELAY ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ ULONG_CMP_GE (unsigned long,unsigned long) ; 
 scalar_t__ ULONG_CMP_LT (unsigned long,unsigned long) ; 
 unsigned long cmpxchg (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int jiffies ; 
 int /*<<< orphan*/  print_cpu_stall (struct rcu_state*) ; 
 int /*<<< orphan*/  print_other_cpu_stall (struct rcu_state*,unsigned long) ; 
 scalar_t__ rcu_cpu_stall_suppress ; 
 scalar_t__ rcu_gp_in_progress (struct rcu_state*) ; 
 int rcu_jiffies_till_stall_check () ; 
 int /*<<< orphan*/  rcu_kick_kthreads ; 
 int /*<<< orphan*/  rcu_stall_kick_kthreads (struct rcu_state*) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static void check_cpu_stall(struct rcu_state *rsp, struct rcu_data *rdp)
{
	unsigned long gs1;
	unsigned long gs2;
	unsigned long gps;
	unsigned long j;
	unsigned long jn;
	unsigned long js;
	struct rcu_node *rnp;

	if ((rcu_cpu_stall_suppress && !rcu_kick_kthreads) ||
	    !rcu_gp_in_progress(rsp))
		return;
	rcu_stall_kick_kthreads(rsp);
	j = jiffies;

	/*
	 * Lots of memory barriers to reject false positives.
	 *
	 * The idea is to pick up rsp->gp_seq, then rsp->jiffies_stall,
	 * then rsp->gp_start, and finally another copy of rsp->gp_seq.
	 * These values are updated in the opposite order with memory
	 * barriers (or equivalent) during grace-period initialization
	 * and cleanup.  Now, a false positive can occur if we get an new
	 * value of rsp->gp_start and a old value of rsp->jiffies_stall.
	 * But given the memory barriers, the only way that this can happen
	 * is if one grace period ends and another starts between these
	 * two fetches.  This is detected by comparing the second fetch
	 * of rsp->gp_seq with the previous fetch from rsp->gp_seq.
	 *
	 * Given this check, comparisons of jiffies, rsp->jiffies_stall,
	 * and rsp->gp_start suffice to forestall false positives.
	 */
	gs1 = READ_ONCE(rsp->gp_seq);
	smp_rmb(); /* Pick up ->gp_seq first... */
	js = READ_ONCE(rsp->jiffies_stall);
	smp_rmb(); /* ...then ->jiffies_stall before the rest... */
	gps = READ_ONCE(rsp->gp_start);
	smp_rmb(); /* ...and finally ->gp_start before ->gp_seq again. */
	gs2 = READ_ONCE(rsp->gp_seq);
	if (gs1 != gs2 ||
	    ULONG_CMP_LT(j, js) ||
	    ULONG_CMP_GE(gps, js))
		return; /* No stall or GP completed since entering function. */
	rnp = rdp->mynode;
	jn = jiffies + 3 * rcu_jiffies_till_stall_check() + 3;
	if (rcu_gp_in_progress(rsp) &&
	    (READ_ONCE(rnp->qsmask) & rdp->grpmask) &&
	    cmpxchg(&rsp->jiffies_stall, js, jn) == js) {

		/* We haven't checked in, so go dump stack. */
		print_cpu_stall(rsp);

	} else if (rcu_gp_in_progress(rsp) &&
		   ULONG_CMP_GE(j, js + RCU_STALL_RAT_DELAY) &&
		   cmpxchg(&rsp->jiffies_stall, js, jn) == js) {

		/* They had a few time units to dump stack, so complain. */
		print_other_cpu_stall(rsp, gs2);
	}
}