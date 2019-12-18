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
struct srcu_struct {int /*<<< orphan*/  srcu_gp_seq; int /*<<< orphan*/  sda; } ;
struct srcu_data {unsigned long srcu_gp_seq_needed; unsigned long srcu_gp_seq_needed_exp; int /*<<< orphan*/  mynode; int /*<<< orphan*/  srcu_cblist; } ;
struct rcu_head {int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  rcu_callback_t ;

/* Variables and functions */
 scalar_t__ ULONG_CMP_LT (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_init_srcu_struct (struct srcu_struct*) ; 
 scalar_t__ debug_rcu_head_queue (struct rcu_head*) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  rcu_segcblist_accelerate (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rcu_segcblist_advance (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_segcblist_enqueue (int /*<<< orphan*/ *,struct rcu_head*,int) ; 
 int /*<<< orphan*/  rcu_seq_current (int /*<<< orphan*/ *) ; 
 unsigned long rcu_seq_snap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_rcu_node (struct srcu_data*) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore_rcu_node (struct srcu_data*,unsigned long) ; 
 int /*<<< orphan*/  srcu_funnel_exp_start (struct srcu_struct*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  srcu_funnel_gp_start (struct srcu_struct*,struct srcu_data*,unsigned long,int) ; 
 int /*<<< orphan*/  srcu_leak_callback ; 
 int srcu_read_lock (struct srcu_struct*) ; 
 int /*<<< orphan*/  srcu_read_unlock (struct srcu_struct*,int) ; 
 struct srcu_data* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __call_srcu(struct srcu_struct *ssp, struct rcu_head *rhp,
			rcu_callback_t func, bool do_norm)
{
	unsigned long flags;
	int idx;
	bool needexp = false;
	bool needgp = false;
	unsigned long s;
	struct srcu_data *sdp;

	check_init_srcu_struct(ssp);
	if (debug_rcu_head_queue(rhp)) {
		/* Probable double call_srcu(), so leak the callback. */
		WRITE_ONCE(rhp->func, srcu_leak_callback);
		WARN_ONCE(1, "call_srcu(): Leaked duplicate callback\n");
		return;
	}
	rhp->func = func;
	idx = srcu_read_lock(ssp);
	local_irq_save(flags);
	sdp = this_cpu_ptr(ssp->sda);
	spin_lock_rcu_node(sdp);
	rcu_segcblist_enqueue(&sdp->srcu_cblist, rhp, false);
	rcu_segcblist_advance(&sdp->srcu_cblist,
			      rcu_seq_current(&ssp->srcu_gp_seq));
	s = rcu_seq_snap(&ssp->srcu_gp_seq);
	(void)rcu_segcblist_accelerate(&sdp->srcu_cblist, s);
	if (ULONG_CMP_LT(sdp->srcu_gp_seq_needed, s)) {
		sdp->srcu_gp_seq_needed = s;
		needgp = true;
	}
	if (!do_norm && ULONG_CMP_LT(sdp->srcu_gp_seq_needed_exp, s)) {
		sdp->srcu_gp_seq_needed_exp = s;
		needexp = true;
	}
	spin_unlock_irqrestore_rcu_node(sdp, flags);
	if (needgp)
		srcu_funnel_gp_start(ssp, sdp, s, do_norm);
	else if (needexp)
		srcu_funnel_exp_start(ssp, sdp->mynode, s);
	srcu_read_unlock(ssp, idx);
}