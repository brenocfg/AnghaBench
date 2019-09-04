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
struct tcf_csum_params {int /*<<< orphan*/  update_flags; } ;
struct tcf_csum {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  params; int /*<<< orphan*/  tcf_action; } ;
struct tc_csum {int /*<<< orphan*/  action; int /*<<< orphan*/  update_flags; int /*<<< orphan*/  index; } ;
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
 int /*<<< orphan*/  TCA_CSUM_MAX ; 
 size_t TCA_CSUM_PARMS ; 
 int /*<<< orphan*/  act_csum_ops ; 
 int /*<<< orphan*/  csum_net_id ; 
 int /*<<< orphan*/  csum_policy ; 
 int /*<<< orphan*/  kfree_rcu (struct tcf_csum_params*,int /*<<< orphan*/ ) ; 
 struct tcf_csum_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct tc_csum* nla_data (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_swap_protected (int /*<<< orphan*/ ,struct tcf_csum_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tcf_idr_check_alloc (struct tc_action_net*,int /*<<< orphan*/ *,struct tc_action**,int) ; 
 int /*<<< orphan*/  tcf_idr_cleanup (struct tc_action_net*,int /*<<< orphan*/ ) ; 
 int tcf_idr_create (struct tc_action_net*,int /*<<< orphan*/ ,struct nlattr*,struct tc_action**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcf_idr_insert (struct tc_action_net*,struct tc_action*) ; 
 int /*<<< orphan*/  tcf_idr_release (struct tc_action*,int) ; 
 struct tcf_csum* to_tcf_csum (struct tc_action*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tcf_csum_init(struct net *net, struct nlattr *nla,
			 struct nlattr *est, struct tc_action **a, int ovr,
			 int bind, bool rtnl_held,
			 struct netlink_ext_ack *extack)
{
	struct tc_action_net *tn = net_generic(net, csum_net_id);
	struct tcf_csum_params *params_new;
	struct nlattr *tb[TCA_CSUM_MAX + 1];
	struct tc_csum *parm;
	struct tcf_csum *p;
	int ret = 0, err;

	if (nla == NULL)
		return -EINVAL;

	err = nla_parse_nested(tb, TCA_CSUM_MAX, nla, csum_policy, NULL);
	if (err < 0)
		return err;

	if (tb[TCA_CSUM_PARMS] == NULL)
		return -EINVAL;
	parm = nla_data(tb[TCA_CSUM_PARMS]);

	err = tcf_idr_check_alloc(tn, &parm->index, a, bind);
	if (!err) {
		ret = tcf_idr_create(tn, parm->index, est, a,
				     &act_csum_ops, bind, true);
		if (ret) {
			tcf_idr_cleanup(tn, parm->index);
			return ret;
		}
		ret = ACT_P_CREATED;
	} else if (err > 0) {
		if (bind)/* dont override defaults */
			return 0;
		if (!ovr) {
			tcf_idr_release(*a, bind);
			return -EEXIST;
		}
	} else {
		return err;
	}

	p = to_tcf_csum(*a);

	params_new = kzalloc(sizeof(*params_new), GFP_KERNEL);
	if (unlikely(!params_new)) {
		tcf_idr_release(*a, bind);
		return -ENOMEM;
	}
	params_new->update_flags = parm->update_flags;

	spin_lock_bh(&p->tcf_lock);
	p->tcf_action = parm->action;
	rcu_swap_protected(p->params, params_new,
			   lockdep_is_held(&p->tcf_lock));
	spin_unlock_bh(&p->tcf_lock);

	if (params_new)
		kfree_rcu(params_new, rcu);

	if (ret == ACT_P_CREATED)
		tcf_idr_insert(tn, *a);

	return ret;
}