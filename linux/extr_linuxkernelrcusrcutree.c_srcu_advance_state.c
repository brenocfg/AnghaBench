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
struct srcu_struct {int srcu_idx; int /*<<< orphan*/  srcu_gp_mutex; int /*<<< orphan*/  srcu_gp_seq; int /*<<< orphan*/  srcu_gp_seq_needed; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int SRCU_STATE_IDLE ; 
 int SRCU_STATE_SCAN1 ; 
 int SRCU_STATE_SCAN2 ; 
 scalar_t__ ULONG_CMP_GE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_seq_set_state (int /*<<< orphan*/ *,int) ; 
 int rcu_seq_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq_rcu_node (struct srcu_struct*) ; 
 int /*<<< orphan*/  spin_unlock_irq_rcu_node (struct srcu_struct*) ; 
 int /*<<< orphan*/  srcu_flip (struct srcu_struct*) ; 
 int /*<<< orphan*/  srcu_gp_end (struct srcu_struct*) ; 
 int /*<<< orphan*/  srcu_gp_start (struct srcu_struct*) ; 
 int /*<<< orphan*/  try_check_zero (struct srcu_struct*,int,int) ; 

__attribute__((used)) static void srcu_advance_state(struct srcu_struct *sp)
{
	int idx;

	mutex_lock(&sp->srcu_gp_mutex);

	/*
	 * Because readers might be delayed for an extended period after
	 * fetching ->srcu_idx for their index, at any point in time there
	 * might well be readers using both idx=0 and idx=1.  We therefore
	 * need to wait for readers to clear from both index values before
	 * invoking a callback.
	 *
	 * The load-acquire ensures that we see the accesses performed
	 * by the prior grace period.
	 */
	idx = rcu_seq_state(smp_load_acquire(&sp->srcu_gp_seq)); /* ^^^ */
	if (idx == SRCU_STATE_IDLE) {
		spin_lock_irq_rcu_node(sp);
		if (ULONG_CMP_GE(sp->srcu_gp_seq, sp->srcu_gp_seq_needed)) {
			WARN_ON_ONCE(rcu_seq_state(sp->srcu_gp_seq));
			spin_unlock_irq_rcu_node(sp);
			mutex_unlock(&sp->srcu_gp_mutex);
			return;
		}
		idx = rcu_seq_state(READ_ONCE(sp->srcu_gp_seq));
		if (idx == SRCU_STATE_IDLE)
			srcu_gp_start(sp);
		spin_unlock_irq_rcu_node(sp);
		if (idx != SRCU_STATE_IDLE) {
			mutex_unlock(&sp->srcu_gp_mutex);
			return; /* Someone else started the grace period. */
		}
	}

	if (rcu_seq_state(READ_ONCE(sp->srcu_gp_seq)) == SRCU_STATE_SCAN1) {
		idx = 1 ^ (sp->srcu_idx & 1);
		if (!try_check_zero(sp, idx, 1)) {
			mutex_unlock(&sp->srcu_gp_mutex);
			return; /* readers present, retry later. */
		}
		srcu_flip(sp);
		rcu_seq_set_state(&sp->srcu_gp_seq, SRCU_STATE_SCAN2);
	}

	if (rcu_seq_state(READ_ONCE(sp->srcu_gp_seq)) == SRCU_STATE_SCAN2) {

		/*
		 * SRCU read-side critical sections are normally short,
		 * so check at least twice in quick succession after a flip.
		 */
		idx = 1 ^ (sp->srcu_idx & 1);
		if (!try_check_zero(sp, idx, 2)) {
			mutex_unlock(&sp->srcu_gp_mutex);
			return; /* readers present, retry later. */
		}
		srcu_gp_end(sp);  /* Releases ->srcu_gp_mutex. */
	}
}