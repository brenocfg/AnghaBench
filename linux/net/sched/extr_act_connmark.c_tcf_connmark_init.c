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
struct tcf_connmark_info {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  zone; struct net* net; } ;
struct tcf_chain {int dummy; } ;
struct tc_connmark {int /*<<< orphan*/  zone; int /*<<< orphan*/  action; int /*<<< orphan*/  index; } ;
struct tc_action_net {int dummy; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  TCA_CONNMARK_MAX ; 
 size_t TCA_CONNMARK_PARMS ; 
 int /*<<< orphan*/  act_connmark_ops ; 
 int /*<<< orphan*/  connmark_net_id ; 
 int /*<<< orphan*/  connmark_policy ; 
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct tc_connmark* nla_data (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tcf_action_check_ctrlact (int /*<<< orphan*/ ,struct tcf_proto*,struct tcf_chain**,struct netlink_ext_ack*) ; 
 struct tcf_chain* tcf_action_set_ctrlact (struct tc_action*,int /*<<< orphan*/ ,struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_put_by_act (struct tcf_chain*) ; 
 int tcf_idr_check_alloc (struct tc_action_net*,int /*<<< orphan*/ *,struct tc_action**,int) ; 
 int /*<<< orphan*/  tcf_idr_cleanup (struct tc_action_net*,int /*<<< orphan*/ ) ; 
 int tcf_idr_create (struct tc_action_net*,int /*<<< orphan*/ ,struct nlattr*,struct tc_action**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcf_idr_insert (struct tc_action_net*,struct tc_action*) ; 
 int /*<<< orphan*/  tcf_idr_release (struct tc_action*,int) ; 
 struct tcf_connmark_info* to_connmark (struct tc_action*) ; 

__attribute__((used)) static int tcf_connmark_init(struct net *net, struct nlattr *nla,
			     struct nlattr *est, struct tc_action **a,
			     int ovr, int bind, bool rtnl_held,
			     struct tcf_proto *tp,
			     struct netlink_ext_ack *extack)
{
	struct tc_action_net *tn = net_generic(net, connmark_net_id);
	struct nlattr *tb[TCA_CONNMARK_MAX + 1];
	struct tcf_chain *goto_ch = NULL;
	struct tcf_connmark_info *ci;
	struct tc_connmark *parm;
	int ret = 0, err;
	u32 index;

	if (!nla)
		return -EINVAL;

	ret = nla_parse_nested_deprecated(tb, TCA_CONNMARK_MAX, nla,
					  connmark_policy, NULL);
	if (ret < 0)
		return ret;

	if (!tb[TCA_CONNMARK_PARMS])
		return -EINVAL;

	parm = nla_data(tb[TCA_CONNMARK_PARMS]);
	index = parm->index;
	ret = tcf_idr_check_alloc(tn, &index, a, bind);
	if (!ret) {
		ret = tcf_idr_create(tn, index, est, a,
				     &act_connmark_ops, bind, false);
		if (ret) {
			tcf_idr_cleanup(tn, index);
			return ret;
		}

		ci = to_connmark(*a);
		err = tcf_action_check_ctrlact(parm->action, tp, &goto_ch,
					       extack);
		if (err < 0)
			goto release_idr;
		tcf_action_set_ctrlact(*a, parm->action, goto_ch);
		ci->net = net;
		ci->zone = parm->zone;

		tcf_idr_insert(tn, *a);
		ret = ACT_P_CREATED;
	} else if (ret > 0) {
		ci = to_connmark(*a);
		if (bind)
			return 0;
		if (!ovr) {
			tcf_idr_release(*a, bind);
			return -EEXIST;
		}
		err = tcf_action_check_ctrlact(parm->action, tp, &goto_ch,
					       extack);
		if (err < 0)
			goto release_idr;
		/* replacing action and zone */
		spin_lock_bh(&ci->tcf_lock);
		goto_ch = tcf_action_set_ctrlact(*a, parm->action, goto_ch);
		ci->zone = parm->zone;
		spin_unlock_bh(&ci->tcf_lock);
		if (goto_ch)
			tcf_chain_put_by_act(goto_ch);
		ret = 0;
	}

	return ret;
release_idr:
	tcf_idr_release(*a, bind);
	return err;
}