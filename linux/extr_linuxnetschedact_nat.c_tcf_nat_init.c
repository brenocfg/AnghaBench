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
struct tcf_nat {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  flags; int /*<<< orphan*/  mask; int /*<<< orphan*/  new_addr; int /*<<< orphan*/  old_addr; } ;
struct tc_nat {int /*<<< orphan*/  action; int /*<<< orphan*/  flags; int /*<<< orphan*/  mask; int /*<<< orphan*/  new_addr; int /*<<< orphan*/  old_addr; int /*<<< orphan*/  index; } ;
struct tc_action_net {int dummy; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  TCA_NAT_MAX ; 
 size_t TCA_NAT_PARMS ; 
 int /*<<< orphan*/  act_nat_ops ; 
 int /*<<< orphan*/  nat_net_id ; 
 int /*<<< orphan*/  nat_policy ; 
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct tc_nat* nla_data (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tcf_idr_check_alloc (struct tc_action_net*,int /*<<< orphan*/ *,struct tc_action**,int) ; 
 int /*<<< orphan*/  tcf_idr_cleanup (struct tc_action_net*,int /*<<< orphan*/ ) ; 
 int tcf_idr_create (struct tc_action_net*,int /*<<< orphan*/ ,struct nlattr*,struct tc_action**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcf_idr_insert (struct tc_action_net*,struct tc_action*) ; 
 int /*<<< orphan*/  tcf_idr_release (struct tc_action*,int) ; 
 struct tcf_nat* to_tcf_nat (struct tc_action*) ; 

__attribute__((used)) static int tcf_nat_init(struct net *net, struct nlattr *nla, struct nlattr *est,
			struct tc_action **a, int ovr, int bind,
			bool rtnl_held, struct netlink_ext_ack *extack)
{
	struct tc_action_net *tn = net_generic(net, nat_net_id);
	struct nlattr *tb[TCA_NAT_MAX + 1];
	struct tc_nat *parm;
	int ret = 0, err;
	struct tcf_nat *p;

	if (nla == NULL)
		return -EINVAL;

	err = nla_parse_nested(tb, TCA_NAT_MAX, nla, nat_policy, NULL);
	if (err < 0)
		return err;

	if (tb[TCA_NAT_PARMS] == NULL)
		return -EINVAL;
	parm = nla_data(tb[TCA_NAT_PARMS]);

	err = tcf_idr_check_alloc(tn, &parm->index, a, bind);
	if (!err) {
		ret = tcf_idr_create(tn, parm->index, est, a,
				     &act_nat_ops, bind, false);
		if (ret) {
			tcf_idr_cleanup(tn, parm->index);
			return ret;
		}
		ret = ACT_P_CREATED;
	} else if (err > 0) {
		if (bind)
			return 0;
		if (!ovr) {
			tcf_idr_release(*a, bind);
			return -EEXIST;
		}
	} else {
		return err;
	}
	p = to_tcf_nat(*a);

	spin_lock_bh(&p->tcf_lock);
	p->old_addr = parm->old_addr;
	p->new_addr = parm->new_addr;
	p->mask = parm->mask;
	p->flags = parm->flags;

	p->tcf_action = parm->action;
	spin_unlock_bh(&p->tcf_lock);

	if (ret == ACT_P_CREATED)
		tcf_idr_insert(tn, *a);

	return ret;
}