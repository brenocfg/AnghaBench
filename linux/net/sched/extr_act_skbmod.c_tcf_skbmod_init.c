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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tcf_skbmod_params {int flags; int /*<<< orphan*/  eth_type; int /*<<< orphan*/  eth_src; int /*<<< orphan*/  eth_dst; } ;
struct tcf_skbmod {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  skbmod_p; } ;
struct tcf_proto {int dummy; } ;
struct tcf_chain {int dummy; } ;
struct tc_skbmod {int index; int flags; int /*<<< orphan*/  action; } ;
struct tc_action_net {int dummy; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SKBMOD_F_DMAC ; 
 int SKBMOD_F_ETYPE ; 
 int SKBMOD_F_SMAC ; 
 int SKBMOD_F_SWAPMAC ; 
 size_t TCA_SKBMOD_DMAC ; 
 size_t TCA_SKBMOD_ETYPE ; 
 int /*<<< orphan*/  TCA_SKBMOD_MAX ; 
 size_t TCA_SKBMOD_PARMS ; 
 size_t TCA_SKBMOD_SMAC ; 
 int /*<<< orphan*/  act_skbmod_ops ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct tcf_skbmod_params*,int /*<<< orphan*/ ) ; 
 struct tcf_skbmod_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 void* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u16 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct tcf_skbmod_params*) ; 
 struct tcf_skbmod_params* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skbmod_net_id ; 
 int /*<<< orphan*/  skbmod_policy ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tcf_action_check_ctrlact (int /*<<< orphan*/ ,struct tcf_proto*,struct tcf_chain**,struct netlink_ext_ack*) ; 
 struct tcf_chain* tcf_action_set_ctrlact (struct tc_action*,int /*<<< orphan*/ ,struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_put_by_act (struct tcf_chain*) ; 
 int tcf_idr_check_alloc (struct tc_action_net*,int*,struct tc_action**,int) ; 
 int /*<<< orphan*/  tcf_idr_cleanup (struct tc_action_net*,int) ; 
 int tcf_idr_create (struct tc_action_net*,int,struct nlattr*,struct tc_action**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcf_idr_insert (struct tc_action_net*,struct tc_action*) ; 
 int /*<<< orphan*/  tcf_idr_release (struct tc_action*,int) ; 
 struct tcf_skbmod* to_skbmod (struct tc_action*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tcf_skbmod_init(struct net *net, struct nlattr *nla,
			   struct nlattr *est, struct tc_action **a,
			   int ovr, int bind, bool rtnl_held,
			   struct tcf_proto *tp,
			   struct netlink_ext_ack *extack)
{
	struct tc_action_net *tn = net_generic(net, skbmod_net_id);
	struct nlattr *tb[TCA_SKBMOD_MAX + 1];
	struct tcf_skbmod_params *p, *p_old;
	struct tcf_chain *goto_ch = NULL;
	struct tc_skbmod *parm;
	u32 lflags = 0, index;
	struct tcf_skbmod *d;
	bool exists = false;
	u8 *daddr = NULL;
	u8 *saddr = NULL;
	u16 eth_type = 0;
	int ret = 0, err;

	if (!nla)
		return -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_SKBMOD_MAX, nla,
					  skbmod_policy, NULL);
	if (err < 0)
		return err;

	if (!tb[TCA_SKBMOD_PARMS])
		return -EINVAL;

	if (tb[TCA_SKBMOD_DMAC]) {
		daddr = nla_data(tb[TCA_SKBMOD_DMAC]);
		lflags |= SKBMOD_F_DMAC;
	}

	if (tb[TCA_SKBMOD_SMAC]) {
		saddr = nla_data(tb[TCA_SKBMOD_SMAC]);
		lflags |= SKBMOD_F_SMAC;
	}

	if (tb[TCA_SKBMOD_ETYPE]) {
		eth_type = nla_get_u16(tb[TCA_SKBMOD_ETYPE]);
		lflags |= SKBMOD_F_ETYPE;
	}

	parm = nla_data(tb[TCA_SKBMOD_PARMS]);
	index = parm->index;
	if (parm->flags & SKBMOD_F_SWAPMAC)
		lflags = SKBMOD_F_SWAPMAC;

	err = tcf_idr_check_alloc(tn, &index, a, bind);
	if (err < 0)
		return err;
	exists = err;
	if (exists && bind)
		return 0;

	if (!lflags) {
		if (exists)
			tcf_idr_release(*a, bind);
		else
			tcf_idr_cleanup(tn, index);
		return -EINVAL;
	}

	if (!exists) {
		ret = tcf_idr_create(tn, index, est, a,
				     &act_skbmod_ops, bind, true);
		if (ret) {
			tcf_idr_cleanup(tn, index);
			return ret;
		}

		ret = ACT_P_CREATED;
	} else if (!ovr) {
		tcf_idr_release(*a, bind);
		return -EEXIST;
	}
	err = tcf_action_check_ctrlact(parm->action, tp, &goto_ch, extack);
	if (err < 0)
		goto release_idr;

	d = to_skbmod(*a);

	p = kzalloc(sizeof(struct tcf_skbmod_params), GFP_KERNEL);
	if (unlikely(!p)) {
		err = -ENOMEM;
		goto put_chain;
	}

	p->flags = lflags;

	if (ovr)
		spin_lock_bh(&d->tcf_lock);
	/* Protected by tcf_lock if overwriting existing action. */
	goto_ch = tcf_action_set_ctrlact(*a, parm->action, goto_ch);
	p_old = rcu_dereference_protected(d->skbmod_p, 1);

	if (lflags & SKBMOD_F_DMAC)
		ether_addr_copy(p->eth_dst, daddr);
	if (lflags & SKBMOD_F_SMAC)
		ether_addr_copy(p->eth_src, saddr);
	if (lflags & SKBMOD_F_ETYPE)
		p->eth_type = htons(eth_type);

	rcu_assign_pointer(d->skbmod_p, p);
	if (ovr)
		spin_unlock_bh(&d->tcf_lock);

	if (p_old)
		kfree_rcu(p_old, rcu);
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);

	if (ret == ACT_P_CREATED)
		tcf_idr_insert(tn, *a);
	return ret;
put_chain:
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
release_idr:
	tcf_idr_release(*a, bind);
	return err;
}