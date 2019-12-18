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
struct tcf_proto {scalar_t__ prio; struct tc_u_common* data; } ;
struct tc_u_knode {int /*<<< orphan*/  flags; int /*<<< orphan*/  next; } ;
struct tc_u_hnode {scalar_t__ prio; unsigned int divisor; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ht; int /*<<< orphan*/  next; } ;
struct tc_u_common {int /*<<< orphan*/  hlist; } ;
struct netlink_ext_ack {int dummy; } ;
typedef  int /*<<< orphan*/  flow_setup_cb_t ;

/* Variables and functions */
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ tc_skip_hw (int /*<<< orphan*/ ) ; 
 int u32_reoffload_hnode (struct tcf_proto*,struct tc_u_hnode*,int,int /*<<< orphan*/ *,void*,struct netlink_ext_ack*) ; 
 int u32_reoffload_knode (struct tcf_proto*,struct tc_u_knode*,int,int /*<<< orphan*/ *,void*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int u32_reoffload(struct tcf_proto *tp, bool add, flow_setup_cb_t *cb,
			 void *cb_priv, struct netlink_ext_ack *extack)
{
	struct tc_u_common *tp_c = tp->data;
	struct tc_u_hnode *ht;
	struct tc_u_knode *n;
	unsigned int h;
	int err;

	for (ht = rtnl_dereference(tp_c->hlist);
	     ht;
	     ht = rtnl_dereference(ht->next)) {
		if (ht->prio != tp->prio)
			continue;

		/* When adding filters to a new dev, try to offload the
		 * hashtable first. When removing, do the filters before the
		 * hashtable.
		 */
		if (add && !tc_skip_hw(ht->flags)) {
			err = u32_reoffload_hnode(tp, ht, add, cb, cb_priv,
						  extack);
			if (err)
				return err;
		}

		for (h = 0; h <= ht->divisor; h++) {
			for (n = rtnl_dereference(ht->ht[h]);
			     n;
			     n = rtnl_dereference(n->next)) {
				if (tc_skip_hw(n->flags))
					continue;

				err = u32_reoffload_knode(tp, n, add, cb,
							  cb_priv, extack);
				if (err)
					return err;
			}
		}

		if (!add && !tc_skip_hw(ht->flags))
			u32_reoffload_hnode(tp, ht, add, cb, cb_priv, extack);
	}

	return 0;
}