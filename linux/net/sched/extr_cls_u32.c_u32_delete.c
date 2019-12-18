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
struct tcf_proto {struct tc_u_common* data; } ;
struct tc_u_knode {int dummy; } ;
struct tc_u_hnode {int refcnt; scalar_t__ is_root; int /*<<< orphan*/  handle; } ;
struct tc_u_common {int refcnt; scalar_t__ knodes; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 scalar_t__ TC_U32_KEY (int /*<<< orphan*/ ) ; 
 int u32_delete_key (struct tcf_proto*,struct tc_u_knode*) ; 
 int /*<<< orphan*/  u32_destroy_hnode (struct tcf_proto*,struct tc_u_hnode*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  u32_remove_hw_knode (struct tcf_proto*,struct tc_u_knode*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int u32_delete(struct tcf_proto *tp, void *arg, bool *last,
		      bool rtnl_held, struct netlink_ext_ack *extack)
{
	struct tc_u_hnode *ht = arg;
	struct tc_u_common *tp_c = tp->data;
	int ret = 0;

	if (TC_U32_KEY(ht->handle)) {
		u32_remove_hw_knode(tp, (struct tc_u_knode *)ht, extack);
		ret = u32_delete_key(tp, (struct tc_u_knode *)ht);
		goto out;
	}

	if (ht->is_root) {
		NL_SET_ERR_MSG_MOD(extack, "Not allowed to delete root node");
		return -EINVAL;
	}

	if (ht->refcnt == 1) {
		u32_destroy_hnode(tp, ht, extack);
	} else {
		NL_SET_ERR_MSG_MOD(extack, "Can not delete in-use filter");
		return -EBUSY;
	}

out:
	*last = tp_c->refcnt == 1 && tp_c->knodes == 0;
	return ret;
}