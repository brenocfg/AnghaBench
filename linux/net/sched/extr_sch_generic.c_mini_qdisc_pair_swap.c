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
struct tcf_proto {int dummy; } ;
struct mini_Qdisc {int /*<<< orphan*/  rcu; struct tcf_proto* filter_list; } ;
struct mini_Qdisc_pair {int /*<<< orphan*/ * p_miniq; struct mini_Qdisc miniq2; struct mini_Qdisc miniq1; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mini_qdisc_rcu_func ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct mini_Qdisc*) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 struct mini_Qdisc* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 

void mini_qdisc_pair_swap(struct mini_Qdisc_pair *miniqp,
			  struct tcf_proto *tp_head)
{
	/* Protected with chain0->filter_chain_lock.
	 * Can't access chain directly because tp_head can be NULL.
	 */
	struct mini_Qdisc *miniq_old =
		rcu_dereference_protected(*miniqp->p_miniq, 1);
	struct mini_Qdisc *miniq;

	if (!tp_head) {
		RCU_INIT_POINTER(*miniqp->p_miniq, NULL);
		/* Wait for flying RCU callback before it is freed. */
		rcu_barrier();
		return;
	}

	miniq = !miniq_old || miniq_old == &miniqp->miniq2 ?
		&miniqp->miniq1 : &miniqp->miniq2;

	/* We need to make sure that readers won't see the miniq
	 * we are about to modify. So wait until previous call_rcu callback
	 * is done.
	 */
	rcu_barrier();
	miniq->filter_list = tp_head;
	rcu_assign_pointer(*miniqp->p_miniq, miniq);

	if (miniq_old)
		/* This is counterpart of the rcu barriers above. We need to
		 * block potential new user of miniq_old until all readers
		 * are not seeing it.
		 */
		call_rcu(&miniq_old->rcu, mini_qdisc_rcu_func);
}