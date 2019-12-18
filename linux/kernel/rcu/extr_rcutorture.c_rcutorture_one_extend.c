#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct torture_random_state {int dummy; } ;
struct rt_read_seg {int rt_readstate; } ;
struct TYPE_2__ {int (* readlock ) () ;int /*<<< orphan*/  (* read_delay ) (struct torture_random_state*,struct rt_read_seg*) ;int /*<<< orphan*/  (* readunlock ) (int) ;} ;

/* Variables and functions */
 int RCUTORTURE_RDR_BH ; 
 int RCUTORTURE_RDR_IRQ ; 
 int RCUTORTURE_RDR_MASK ; 
 int RCUTORTURE_RDR_PREEMPT ; 
 int RCUTORTURE_RDR_RBH ; 
 int RCUTORTURE_RDR_RCU ; 
 int RCUTORTURE_RDR_SCHED ; 
 int RCUTORTURE_RDR_SHIFT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 TYPE_1__* cur_ops ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_lock_sched () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_sched () ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  stub3 (struct torture_random_state*,struct rt_read_seg*) ; 

__attribute__((used)) static void rcutorture_one_extend(int *readstate, int newstate,
				  struct torture_random_state *trsp,
				  struct rt_read_seg *rtrsp)
{
	int idxnew = -1;
	int idxold = *readstate;
	int statesnew = ~*readstate & newstate;
	int statesold = *readstate & ~newstate;

	WARN_ON_ONCE(idxold < 0);
	WARN_ON_ONCE((idxold >> RCUTORTURE_RDR_SHIFT) > 1);
	rtrsp->rt_readstate = newstate;

	/* First, put new protection in place to avoid critical-section gap. */
	if (statesnew & RCUTORTURE_RDR_BH)
		local_bh_disable();
	if (statesnew & RCUTORTURE_RDR_IRQ)
		local_irq_disable();
	if (statesnew & RCUTORTURE_RDR_PREEMPT)
		preempt_disable();
	if (statesnew & RCUTORTURE_RDR_RBH)
		rcu_read_lock_bh();
	if (statesnew & RCUTORTURE_RDR_SCHED)
		rcu_read_lock_sched();
	if (statesnew & RCUTORTURE_RDR_RCU)
		idxnew = cur_ops->readlock() << RCUTORTURE_RDR_SHIFT;

	/* Next, remove old protection, irq first due to bh conflict. */
	if (statesold & RCUTORTURE_RDR_IRQ)
		local_irq_enable();
	if (statesold & RCUTORTURE_RDR_BH)
		local_bh_enable();
	if (statesold & RCUTORTURE_RDR_PREEMPT)
		preempt_enable();
	if (statesold & RCUTORTURE_RDR_RBH)
		rcu_read_unlock_bh();
	if (statesold & RCUTORTURE_RDR_SCHED)
		rcu_read_unlock_sched();
	if (statesold & RCUTORTURE_RDR_RCU)
		cur_ops->readunlock(idxold >> RCUTORTURE_RDR_SHIFT);

	/* Delay if neither beginning nor end and there was a change. */
	if ((statesnew || statesold) && *readstate && newstate)
		cur_ops->read_delay(trsp, rtrsp);

	/* Update the reader state. */
	if (idxnew == -1)
		idxnew = idxold & ~RCUTORTURE_RDR_MASK;
	WARN_ON_ONCE(idxnew < 0);
	WARN_ON_ONCE((idxnew >> RCUTORTURE_RDR_SHIFT) > 1);
	*readstate = idxnew | newstate;
	WARN_ON_ONCE((*readstate >> RCUTORTURE_RDR_SHIFT) < 0);
	WARN_ON_ONCE((*readstate >> RCUTORTURE_RDR_SHIFT) > 1);
}