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
struct tcf_defact {int /*<<< orphan*/  tcf_action; } ;
struct tc_defact {int /*<<< orphan*/  action; int /*<<< orphan*/  index; } ;
struct tc_action_net {int dummy; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EEXIST ; 
 int EINVAL ; 
 size_t TCA_DEF_DATA ; 
 int /*<<< orphan*/  TCA_DEF_MAX ; 
 size_t TCA_DEF_PARMS ; 
 int /*<<< orphan*/  act_simp_ops ; 
 int alloc_defdata (struct tcf_defact*,struct nlattr*) ; 
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct tc_defact* nla_data (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_policy (struct tcf_defact*,struct nlattr*,struct tc_defact*) ; 
 int /*<<< orphan*/  simp_net_id ; 
 int /*<<< orphan*/  simple_policy ; 
 int tcf_idr_check_alloc (struct tc_action_net*,int /*<<< orphan*/ *,struct tc_action**,int) ; 
 int /*<<< orphan*/  tcf_idr_cleanup (struct tc_action_net*,int /*<<< orphan*/ ) ; 
 int tcf_idr_create (struct tc_action_net*,int /*<<< orphan*/ ,struct nlattr*,struct tc_action**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcf_idr_insert (struct tc_action_net*,struct tc_action*) ; 
 int /*<<< orphan*/  tcf_idr_release (struct tc_action*,int) ; 
 struct tcf_defact* to_defact (struct tc_action*) ; 

__attribute__((used)) static int tcf_simp_init(struct net *net, struct nlattr *nla,
			 struct nlattr *est, struct tc_action **a,
			 int ovr, int bind, bool rtnl_held,
			 struct netlink_ext_ack *extack)
{
	struct tc_action_net *tn = net_generic(net, simp_net_id);
	struct nlattr *tb[TCA_DEF_MAX + 1];
	struct tc_defact *parm;
	struct tcf_defact *d;
	bool exists = false;
	int ret = 0, err;

	if (nla == NULL)
		return -EINVAL;

	err = nla_parse_nested(tb, TCA_DEF_MAX, nla, simple_policy, NULL);
	if (err < 0)
		return err;

	if (tb[TCA_DEF_PARMS] == NULL)
		return -EINVAL;

	parm = nla_data(tb[TCA_DEF_PARMS]);
	err = tcf_idr_check_alloc(tn, &parm->index, a, bind);
	if (err < 0)
		return err;
	exists = err;
	if (exists && bind)
		return 0;

	if (tb[TCA_DEF_DATA] == NULL) {
		if (exists)
			tcf_idr_release(*a, bind);
		else
			tcf_idr_cleanup(tn, parm->index);
		return -EINVAL;
	}

	if (!exists) {
		ret = tcf_idr_create(tn, parm->index, est, a,
				     &act_simp_ops, bind, false);
		if (ret) {
			tcf_idr_cleanup(tn, parm->index);
			return ret;
		}

		d = to_defact(*a);
		ret = alloc_defdata(d, tb[TCA_DEF_DATA]);
		if (ret < 0) {
			tcf_idr_release(*a, bind);
			return ret;
		}
		d->tcf_action = parm->action;
		ret = ACT_P_CREATED;
	} else {
		d = to_defact(*a);

		if (!ovr) {
			tcf_idr_release(*a, bind);
			return -EEXIST;
		}

		reset_policy(d, tb[TCA_DEF_DATA], parm);
	}

	if (ret == ACT_P_CREATED)
		tcf_idr_insert(tn, *a);
	return ret;
}