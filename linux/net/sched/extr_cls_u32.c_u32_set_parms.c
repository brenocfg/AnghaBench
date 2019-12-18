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
typedef  void* u32 ;
struct tcf_proto {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {void* classid; } ;
struct tc_u_knode {int ifindex; TYPE_1__ res; int /*<<< orphan*/  ht_down; int /*<<< orphan*/  exts; } ;
struct tc_u_hnode {int /*<<< orphan*/  refcnt; scalar_t__ is_root; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 size_t TCA_U32_CLASSID ; 
 size_t TCA_U32_INDEV ; 
 size_t TCA_U32_LINK ; 
 scalar_t__ TC_U32_KEY (void*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct tc_u_hnode*) ; 
 struct tc_u_hnode* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_bind_filter (struct tcf_proto*,TYPE_1__*,unsigned long) ; 
 int tcf_change_indev (struct net*,struct nlattr*,struct netlink_ext_ack*) ; 
 int tcf_exts_validate (struct net*,struct tcf_proto*,struct nlattr**,struct nlattr*,int /*<<< orphan*/ *,int,int,struct netlink_ext_ack*) ; 
 struct tc_u_hnode* u32_lookup_ht (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int u32_set_parms(struct net *net, struct tcf_proto *tp,
			 unsigned long base,
			 struct tc_u_knode *n, struct nlattr **tb,
			 struct nlattr *est, bool ovr,
			 struct netlink_ext_ack *extack)
{
	int err;

	err = tcf_exts_validate(net, tp, tb, est, &n->exts, ovr, true, extack);
	if (err < 0)
		return err;

	if (tb[TCA_U32_LINK]) {
		u32 handle = nla_get_u32(tb[TCA_U32_LINK]);
		struct tc_u_hnode *ht_down = NULL, *ht_old;

		if (TC_U32_KEY(handle)) {
			NL_SET_ERR_MSG_MOD(extack, "u32 Link handle must be a hash table");
			return -EINVAL;
		}

		if (handle) {
			ht_down = u32_lookup_ht(tp->data, handle);

			if (!ht_down) {
				NL_SET_ERR_MSG_MOD(extack, "Link hash table not found");
				return -EINVAL;
			}
			if (ht_down->is_root) {
				NL_SET_ERR_MSG_MOD(extack, "Not linking to root node");
				return -EINVAL;
			}
			ht_down->refcnt++;
		}

		ht_old = rtnl_dereference(n->ht_down);
		rcu_assign_pointer(n->ht_down, ht_down);

		if (ht_old)
			ht_old->refcnt--;
	}
	if (tb[TCA_U32_CLASSID]) {
		n->res.classid = nla_get_u32(tb[TCA_U32_CLASSID]);
		tcf_bind_filter(tp, &n->res, base);
	}

	if (tb[TCA_U32_INDEV]) {
		int ret;
		ret = tcf_change_indev(net, tb[TCA_U32_INDEV], extack);
		if (ret < 0)
			return -EINVAL;
		n->ifindex = ret;
	}
	return 0;
}