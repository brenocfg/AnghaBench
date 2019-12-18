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
struct srcu_struct {scalar_t__ srcu_last_gp_end; int /*<<< orphan*/  srcu_gp_seq; int /*<<< orphan*/  srcu_gp_seq_needed; int /*<<< orphan*/  sda; } ;
struct srcu_data {int /*<<< orphan*/  srcu_cblist; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ ULONG_CMP_LT (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ exp_holdoff ; 
 unsigned long ktime_get_mono_fast_ns () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ rcu_segcblist_pend_cbs (int /*<<< orphan*/ *) ; 
 unsigned long rcu_seq_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 struct srcu_data* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ time_in_range_open (unsigned long,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool srcu_might_be_idle(struct srcu_struct *ssp)
{
	unsigned long curseq;
	unsigned long flags;
	struct srcu_data *sdp;
	unsigned long t;

	/* If the local srcu_data structure has callbacks, not idle.  */
	local_irq_save(flags);
	sdp = this_cpu_ptr(ssp->sda);
	if (rcu_segcblist_pend_cbs(&sdp->srcu_cblist)) {
		local_irq_restore(flags);
		return false; /* Callbacks already present, so not idle. */
	}
	local_irq_restore(flags);

	/*
	 * No local callbacks, so probabalistically probe global state.
	 * Exact information would require acquiring locks, which would
	 * kill scalability, hence the probabalistic nature of the probe.
	 */

	/* First, see if enough time has passed since the last GP. */
	t = ktime_get_mono_fast_ns();
	if (exp_holdoff == 0 ||
	    time_in_range_open(t, ssp->srcu_last_gp_end,
			       ssp->srcu_last_gp_end + exp_holdoff))
		return false; /* Too soon after last GP. */

	/* Next, check for probable idleness. */
	curseq = rcu_seq_current(&ssp->srcu_gp_seq);
	smp_mb(); /* Order ->srcu_gp_seq with ->srcu_gp_seq_needed. */
	if (ULONG_CMP_LT(curseq, READ_ONCE(ssp->srcu_gp_seq_needed)))
		return false; /* Grace period in progress, so not idle. */
	smp_mb(); /* Order ->srcu_gp_seq with prior access. */
	if (curseq != rcu_seq_current(&ssp->srcu_gp_seq))
		return false; /* GP # changed, so not idle. */
	return true; /* With reasonable probability, idle! */
}