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
struct rcu_node {int /*<<< orphan*/  gp_seq; } ;
struct TYPE_3__ {int /*<<< orphan*/  norm; } ;
struct TYPE_4__ {TYPE_1__ b; } ;
struct rcu_data {scalar_t__ gp_seq; int /*<<< orphan*/  gpwrap; int /*<<< orphan*/  cblist; TYPE_2__ cpu_no_qs; scalar_t__ core_needs_qs; struct rcu_node* mynode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_RCU_NOCB_CPU ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCU_NEXT_READY_TAIL ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_cpu_stall (struct rcu_data*) ; 
 int /*<<< orphan*/  rcu_data ; 
 int /*<<< orphan*/  rcu_gp_in_progress () ; 
 scalar_t__ rcu_nocb_need_deferred_wakeup (struct rcu_data*) ; 
 scalar_t__ rcu_nohz_full_cpu () ; 
 scalar_t__ rcu_segcblist_is_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_segcblist_is_offloaded (int /*<<< orphan*/ *) ; 
 scalar_t__ rcu_segcblist_ready_cbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_segcblist_restempty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rcu_seq_current (int /*<<< orphan*/ *) ; 
 struct rcu_data* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcu_pending(void)
{
	struct rcu_data *rdp = this_cpu_ptr(&rcu_data);
	struct rcu_node *rnp = rdp->mynode;

	/* Check for CPU stalls, if enabled. */
	check_cpu_stall(rdp);

	/* Does this CPU need a deferred NOCB wakeup? */
	if (rcu_nocb_need_deferred_wakeup(rdp))
		return 1;

	/* Is this CPU a NO_HZ_FULL CPU that should ignore RCU? */
	if (rcu_nohz_full_cpu())
		return 0;

	/* Is the RCU core waiting for a quiescent state from this CPU? */
	if (rdp->core_needs_qs && !rdp->cpu_no_qs.b.norm)
		return 1;

	/* Does this CPU have callbacks ready to invoke? */
	if (rcu_segcblist_ready_cbs(&rdp->cblist))
		return 1;

	/* Has RCU gone idle with this CPU needing another grace period? */
	if (!rcu_gp_in_progress() &&
	    rcu_segcblist_is_enabled(&rdp->cblist) &&
	    (!IS_ENABLED(CONFIG_RCU_NOCB_CPU) ||
	     !rcu_segcblist_is_offloaded(&rdp->cblist)) &&
	    !rcu_segcblist_restempty(&rdp->cblist, RCU_NEXT_READY_TAIL))
		return 1;

	/* Have RCU grace period completed or started?  */
	if (rcu_seq_current(&rnp->gp_seq) != rdp->gp_seq ||
	    unlikely(READ_ONCE(rdp->gpwrap))) /* outside lock */
		return 1;

	/* nothing to do */
	return 0;
}