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
typedef  int u8 ;
typedef  int u32 ;
struct tcf_proto {int dummy; } ;
struct tcf_ctinfo_params {int dscpmask; int dscpmaskshift; int dscpstatemask; int /*<<< orphan*/  mode; void* cpmarkmask; int /*<<< orphan*/  zone; struct net* net; } ;
struct tcf_ctinfo {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  params; } ;
struct tcf_chain {int dummy; } ;
struct tc_ctinfo {int index; int /*<<< orphan*/  action; } ;
struct tc_action_net {int dummy; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int /*<<< orphan*/  CTINFO_MODE_CPMARK ; 
 int /*<<< orphan*/  CTINFO_MODE_DSCP ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_ATTR (struct netlink_ext_ack*,struct nlattr*,char*) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 size_t TCA_CTINFO_ACT ; 
 int /*<<< orphan*/  TCA_CTINFO_MAX ; 
 size_t TCA_CTINFO_PARMS_CPMARK_MASK ; 
 size_t TCA_CTINFO_PARMS_DSCP_MASK ; 
 size_t TCA_CTINFO_PARMS_DSCP_STATEMASK ; 
 size_t TCA_CTINFO_ZONE ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  act_ctinfo_ops ; 
 int /*<<< orphan*/  ctinfo_net_id ; 
 int /*<<< orphan*/  ctinfo_policy ; 
 int /*<<< orphan*/  kfree_rcu (struct tcf_ctinfo_params*,int /*<<< orphan*/ ) ; 
 struct tcf_ctinfo_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct tc_ctinfo* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u16 (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_swap_protected (int /*<<< orphan*/ ,struct tcf_ctinfo_params*,int /*<<< orphan*/ ) ; 
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
 struct tcf_ctinfo* to_ctinfo (struct tc_action*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tcf_ctinfo_init(struct net *net, struct nlattr *nla,
			   struct nlattr *est, struct tc_action **a,
			   int ovr, int bind, bool rtnl_held,
			   struct tcf_proto *tp,
			   struct netlink_ext_ack *extack)
{
	struct tc_action_net *tn = net_generic(net, ctinfo_net_id);
	u32 dscpmask = 0, dscpstatemask, index;
	struct nlattr *tb[TCA_CTINFO_MAX + 1];
	struct tcf_ctinfo_params *cp_new;
	struct tcf_chain *goto_ch = NULL;
	struct tc_ctinfo *actparm;
	struct tcf_ctinfo *ci;
	u8 dscpmaskshift;
	int ret = 0, err;

	if (!nla) {
		NL_SET_ERR_MSG_MOD(extack, "ctinfo requires attributes to be passed");
		return -EINVAL;
	}

	err = nla_parse_nested(tb, TCA_CTINFO_MAX, nla, ctinfo_policy, extack);
	if (err < 0)
		return err;

	if (!tb[TCA_CTINFO_ACT]) {
		NL_SET_ERR_MSG_MOD(extack,
				   "Missing required TCA_CTINFO_ACT attribute");
		return -EINVAL;
	}
	actparm = nla_data(tb[TCA_CTINFO_ACT]);

	/* do some basic validation here before dynamically allocating things */
	/* that we would otherwise have to clean up.			      */
	if (tb[TCA_CTINFO_PARMS_DSCP_MASK]) {
		dscpmask = nla_get_u32(tb[TCA_CTINFO_PARMS_DSCP_MASK]);
		/* need contiguous 6 bit mask */
		dscpmaskshift = dscpmask ? __ffs(dscpmask) : 0;
		if ((~0 & (dscpmask >> dscpmaskshift)) != 0x3f) {
			NL_SET_ERR_MSG_ATTR(extack,
					    tb[TCA_CTINFO_PARMS_DSCP_MASK],
					    "dscp mask must be 6 contiguous bits");
			return -EINVAL;
		}
		dscpstatemask = tb[TCA_CTINFO_PARMS_DSCP_STATEMASK] ?
			nla_get_u32(tb[TCA_CTINFO_PARMS_DSCP_STATEMASK]) : 0;
		/* mask & statemask must not overlap */
		if (dscpmask & dscpstatemask) {
			NL_SET_ERR_MSG_ATTR(extack,
					    tb[TCA_CTINFO_PARMS_DSCP_STATEMASK],
					    "dscp statemask must not overlap dscp mask");
			return -EINVAL;
		}
	}

	/* done the validation:now to the actual action allocation */
	index = actparm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	if (!err) {
		ret = tcf_idr_create(tn, index, est, a,
				     &act_ctinfo_ops, bind, false);
		if (ret) {
			tcf_idr_cleanup(tn, index);
			return ret;
		}
		ret = ACT_P_CREATED;
	} else if (err > 0) {
		if (bind) /* don't override defaults */
			return 0;
		if (!ovr) {
			tcf_idr_release(*a, bind);
			return -EEXIST;
		}
	} else {
		return err;
	}

	err = tcf_action_check_ctrlact(actparm->action, tp, &goto_ch, extack);
	if (err < 0)
		goto release_idr;

	ci = to_ctinfo(*a);

	cp_new = kzalloc(sizeof(*cp_new), GFP_KERNEL);
	if (unlikely(!cp_new)) {
		err = -ENOMEM;
		goto put_chain;
	}

	cp_new->net = net;
	cp_new->zone = tb[TCA_CTINFO_ZONE] ?
			nla_get_u16(tb[TCA_CTINFO_ZONE]) : 0;
	if (dscpmask) {
		cp_new->dscpmask = dscpmask;
		cp_new->dscpmaskshift = dscpmaskshift;
		cp_new->dscpstatemask = dscpstatemask;
		cp_new->mode |= CTINFO_MODE_DSCP;
	}

	if (tb[TCA_CTINFO_PARMS_CPMARK_MASK]) {
		cp_new->cpmarkmask =
				nla_get_u32(tb[TCA_CTINFO_PARMS_CPMARK_MASK]);
		cp_new->mode |= CTINFO_MODE_CPMARK;
	}

	spin_lock_bh(&ci->tcf_lock);
	goto_ch = tcf_action_set_ctrlact(*a, actparm->action, goto_ch);
	rcu_swap_protected(ci->params, cp_new,
			   lockdep_is_held(&ci->tcf_lock));
	spin_unlock_bh(&ci->tcf_lock);

	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
	if (cp_new)
		kfree_rcu(cp_new, rcu);

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