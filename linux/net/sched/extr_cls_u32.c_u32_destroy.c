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
struct tcf_proto {struct tc_u_common* data; int /*<<< orphan*/  root; } ;
struct tc_u_hnode {int refcnt; int /*<<< orphan*/  next; } ;
struct tc_u_common {scalar_t__ refcnt; int /*<<< orphan*/  handle_idr; int /*<<< orphan*/  hlist; int /*<<< orphan*/  hnode; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tc_u_common*) ; 
 int /*<<< orphan*/  kfree_rcu (struct tc_u_hnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 struct tc_u_hnode* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32_clear_hnode (struct tcf_proto*,struct tc_u_hnode*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  u32_destroy_hnode (struct tcf_proto*,struct tc_u_hnode*,struct netlink_ext_ack*) ; 

__attribute__((used)) static void u32_destroy(struct tcf_proto *tp, bool rtnl_held,
			struct netlink_ext_ack *extack)
{
	struct tc_u_common *tp_c = tp->data;
	struct tc_u_hnode *root_ht = rtnl_dereference(tp->root);

	WARN_ON(root_ht == NULL);

	if (root_ht && --root_ht->refcnt == 1)
		u32_destroy_hnode(tp, root_ht, extack);

	if (--tp_c->refcnt == 0) {
		struct tc_u_hnode *ht;

		hlist_del(&tp_c->hnode);

		while ((ht = rtnl_dereference(tp_c->hlist)) != NULL) {
			u32_clear_hnode(tp, ht, extack);
			RCU_INIT_POINTER(tp_c->hlist, ht->next);

			/* u32_destroy_key() will later free ht for us, if it's
			 * still referenced by some knode
			 */
			if (--ht->refcnt == 0)
				kfree_rcu(ht, rcu);
		}

		idr_destroy(&tp_c->handle_idr);
		kfree(tp_c);
	}

	tp->data = NULL;
}