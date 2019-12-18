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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_proto {int dummy; } ;
struct tcf_chain_info {int dummy; } ;
struct tcf_chain {int /*<<< orphan*/  filter_chain_lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 struct tcf_proto* ERR_PTR (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tcf_proto* tcf_chain_tp_find (struct tcf_chain*,struct tcf_chain_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int tcf_chain_tp_insert (struct tcf_chain*,struct tcf_chain_info*,struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_proto_destroy (struct tcf_proto*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ tcf_proto_exists_destroying (struct tcf_chain*,struct tcf_proto*) ; 

__attribute__((used)) static struct tcf_proto *tcf_chain_tp_insert_unique(struct tcf_chain *chain,
						    struct tcf_proto *tp_new,
						    u32 protocol, u32 prio,
						    bool rtnl_held)
{
	struct tcf_chain_info chain_info;
	struct tcf_proto *tp;
	int err = 0;

	mutex_lock(&chain->filter_chain_lock);

	if (tcf_proto_exists_destroying(chain, tp_new)) {
		mutex_unlock(&chain->filter_chain_lock);
		tcf_proto_destroy(tp_new, rtnl_held, false, NULL);
		return ERR_PTR(-EAGAIN);
	}

	tp = tcf_chain_tp_find(chain, &chain_info,
			       protocol, prio, false);
	if (!tp)
		err = tcf_chain_tp_insert(chain, &chain_info, tp_new);
	mutex_unlock(&chain->filter_chain_lock);

	if (tp) {
		tcf_proto_destroy(tp_new, rtnl_held, false, NULL);
		tp_new = tp;
	} else if (err) {
		tcf_proto_destroy(tp_new, rtnl_held, false, NULL);
		tp_new = ERR_PTR(err);
	}

	return tp_new;
}