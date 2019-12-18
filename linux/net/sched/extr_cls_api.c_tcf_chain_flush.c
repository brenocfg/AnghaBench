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
struct tcf_proto {int /*<<< orphan*/  next; } ;
struct tcf_chain {int flushing; int /*<<< orphan*/  filter_chain_lock; int /*<<< orphan*/  filter_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tcf_proto* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcf_chain0_head_change (struct tcf_chain*,int /*<<< orphan*/ *) ; 
 struct tcf_proto* tcf_chain_dereference (int /*<<< orphan*/ ,struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_proto_put (struct tcf_proto*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_proto_signal_destroying (struct tcf_chain*,struct tcf_proto*) ; 

__attribute__((used)) static void tcf_chain_flush(struct tcf_chain *chain, bool rtnl_held)
{
	struct tcf_proto *tp, *tp_next;

	mutex_lock(&chain->filter_chain_lock);
	tp = tcf_chain_dereference(chain->filter_chain, chain);
	while (tp) {
		tp_next = rcu_dereference_protected(tp->next, 1);
		tcf_proto_signal_destroying(chain, tp);
		tp = tp_next;
	}
	tp = tcf_chain_dereference(chain->filter_chain, chain);
	RCU_INIT_POINTER(chain->filter_chain, NULL);
	tcf_chain0_head_change(chain, NULL);
	chain->flushing = true;
	mutex_unlock(&chain->filter_chain_lock);

	while (tp) {
		tp_next = rcu_dereference_protected(tp->next, 1);
		tcf_proto_put(tp, rtnl_held, NULL);
		tp = tp_next;
	}
}