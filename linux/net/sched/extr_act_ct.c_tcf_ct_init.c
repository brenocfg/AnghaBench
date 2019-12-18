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
struct tcf_ct_params {int dummy; } ;
struct tcf_ct {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  params; } ;
struct tcf_chain {int dummy; } ;
struct tc_ct {int /*<<< orphan*/  action; int /*<<< orphan*/  index; } ;
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
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  TCA_CT_MAX ; 
 size_t TCA_CT_PARMS ; 
 int /*<<< orphan*/  act_ct_ops ; 
 int /*<<< orphan*/  ct_net_id ; 
 int /*<<< orphan*/  ct_policy ; 
 int /*<<< orphan*/  kfree (struct tcf_ct_params*) ; 
 int /*<<< orphan*/  kfree_rcu (struct tcf_ct_params*,int /*<<< orphan*/ ) ; 
 struct tcf_ct_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct tc_ct* nla_data (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_swap_protected (int /*<<< orphan*/ ,struct tcf_ct_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tcf_action_check_ctrlact (int /*<<< orphan*/ ,struct tcf_proto*,struct tcf_chain**,struct netlink_ext_ack*) ; 
 struct tcf_chain* tcf_action_set_ctrlact (struct tc_action*,int /*<<< orphan*/ ,struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_put_by_act (struct tcf_chain*) ; 
 int tcf_ct_fill_params (struct net*,struct tcf_ct_params*,struct tc_ct*,struct nlattr**,struct netlink_ext_ack*) ; 
 int tcf_idr_check_alloc (struct tc_action_net*,int /*<<< orphan*/ *,struct tc_action**,int) ; 
 int /*<<< orphan*/  tcf_idr_cleanup (struct tc_action_net*,int /*<<< orphan*/ ) ; 
 int tcf_idr_create (struct tc_action_net*,int /*<<< orphan*/ ,struct nlattr*,struct tc_action**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcf_idr_insert (struct tc_action_net*,struct tc_action*) ; 
 int /*<<< orphan*/  tcf_idr_release (struct tc_action*,int) ; 
 struct tcf_ct* to_ct (struct tc_action*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tcf_ct_init(struct net *net, struct nlattr *nla,
		       struct nlattr *est, struct tc_action **a,
		       int replace, int bind, bool rtnl_held,
		       struct tcf_proto *tp,
		       struct netlink_ext_ack *extack)
{
	struct tc_action_net *tn = net_generic(net, ct_net_id);
	struct tcf_ct_params *params = NULL;
	struct nlattr *tb[TCA_CT_MAX + 1];
	struct tcf_chain *goto_ch = NULL;
	struct tc_ct *parm;
	struct tcf_ct *c;
	int err, res = 0;
	u32 index;

	if (!nla) {
		NL_SET_ERR_MSG_MOD(extack, "Ct requires attributes to be passed");
		return -EINVAL;
	}

	err = nla_parse_nested(tb, TCA_CT_MAX, nla, ct_policy, extack);
	if (err < 0)
		return err;

	if (!tb[TCA_CT_PARMS]) {
		NL_SET_ERR_MSG_MOD(extack, "Missing required ct parameters");
		return -EINVAL;
	}
	parm = nla_data(tb[TCA_CT_PARMS]);
	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	if (err < 0)
		return err;

	if (!err) {
		err = tcf_idr_create(tn, index, est, a,
				     &act_ct_ops, bind, true);
		if (err) {
			tcf_idr_cleanup(tn, index);
			return err;
		}
		res = ACT_P_CREATED;
	} else {
		if (bind)
			return 0;

		if (!replace) {
			tcf_idr_release(*a, bind);
			return -EEXIST;
		}
	}
	err = tcf_action_check_ctrlact(parm->action, tp, &goto_ch, extack);
	if (err < 0)
		goto cleanup;

	c = to_ct(*a);

	params = kzalloc(sizeof(*params), GFP_KERNEL);
	if (unlikely(!params)) {
		err = -ENOMEM;
		goto cleanup;
	}

	err = tcf_ct_fill_params(net, params, parm, tb, extack);
	if (err)
		goto cleanup;

	spin_lock_bh(&c->tcf_lock);
	goto_ch = tcf_action_set_ctrlact(*a, parm->action, goto_ch);
	rcu_swap_protected(c->params, params, lockdep_is_held(&c->tcf_lock));
	spin_unlock_bh(&c->tcf_lock);

	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
	if (params)
		kfree_rcu(params, rcu);
	if (res == ACT_P_CREATED)
		tcf_idr_insert(tn, *a);

	return res;

cleanup:
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
	kfree(params);
	tcf_idr_release(*a, bind);
	return err;
}