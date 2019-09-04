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
struct tcf_connmark_info {int /*<<< orphan*/  zone; int /*<<< orphan*/  tcf_action; struct net* net; } ;
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
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tcf_idr_check_alloc (struct tc_action_net*,int /*<<< orphan*/ *,struct tc_action**,int) ; 
 int /*<<< orphan*/  tcf_idr_cleanup (struct tc_action_net*,int /*<<< orphan*/ ) ; 
 int tcf_idr_create (struct tc_action_net*,int /*<<< orphan*/ ,struct nlattr*,struct tc_action**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcf_idr_insert (struct tc_action_net*,struct tc_action*) ; 
 int /*<<< orphan*/  tcf_idr_release (struct tc_action*,int) ; 
 struct tcf_connmark_info* to_connmark (struct tc_action*) ; 

__attribute__((used)) static int tcf_connmark_init(struct net *net, struct nlattr *nla,
			     struct nlattr *est, struct tc_action **a,
			     int ovr, int bind, bool rtnl_held,
			     struct netlink_ext_ack *extack)
{
	struct tc_action_net *tn = net_generic(net, connmark_net_id);
	struct nlattr *tb[TCA_CONNMARK_MAX + 1];
	struct tcf_connmark_info *ci;
	struct tc_connmark *parm;
	int ret = 0;

	if (!nla)
		return -EINVAL;

	ret = nla_parse_nested(tb, TCA_CONNMARK_MAX, nla, connmark_policy,
			       NULL);
	if (ret < 0)
		return ret;

	if (!tb[TCA_CONNMARK_PARMS])
		return -EINVAL;

	parm = nla_data(tb[TCA_CONNMARK_PARMS]);

	ret = tcf_idr_check_alloc(tn, &parm->index, a, bind);
	if (!ret) {
		ret = tcf_idr_create(tn, parm->index, est, a,
				     &act_connmark_ops, bind, false);
		if (ret) {
			tcf_idr_cleanup(tn, parm->index);
			return ret;
		}

		ci = to_connmark(*a);
		ci->tcf_action = parm->action;
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
		/* replacing action and zone */
		ci->tcf_action = parm->action;
		ci->zone = parm->zone;
		ret = 0;
	}

	return ret;
}