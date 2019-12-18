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
struct tcf_defact {int dummy; } ;
struct tcf_chain {int dummy; } ;
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
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int reset_policy (struct tc_action*,struct nlattr*,struct tc_defact*,struct tcf_proto*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  simp_net_id ; 
 int /*<<< orphan*/  simple_policy ; 
 int tcf_action_check_ctrlact (int /*<<< orphan*/ ,struct tcf_proto*,struct tcf_chain**,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  tcf_action_set_ctrlact (struct tc_action*,int /*<<< orphan*/ ,struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_put_by_act (struct tcf_chain*) ; 
 int tcf_idr_check_alloc (struct tc_action_net*,int /*<<< orphan*/ *,struct tc_action**,int) ; 
 int /*<<< orphan*/  tcf_idr_cleanup (struct tc_action_net*,int /*<<< orphan*/ ) ; 
 int tcf_idr_create (struct tc_action_net*,int /*<<< orphan*/ ,struct nlattr*,struct tc_action**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcf_idr_insert (struct tc_action_net*,struct tc_action*) ; 
 int /*<<< orphan*/  tcf_idr_release (struct tc_action*,int) ; 
 struct tcf_defact* to_defact (struct tc_action*) ; 

__attribute__((used)) static int tcf_simp_init(struct net *net, struct nlattr *nla,
			 struct nlattr *est, struct tc_action **a,
			 int ovr, int bind, bool rtnl_held,
			 struct tcf_proto *tp, struct netlink_ext_ack *extack)
{
	struct tc_action_net *tn = net_generic(net, simp_net_id);
	struct nlattr *tb[TCA_DEF_MAX + 1];
	struct tcf_chain *goto_ch = NULL;
	struct tc_defact *parm;
	struct tcf_defact *d;
	bool exists = false;
	int ret = 0, err;
	u32 index;

	if (nla == NULL)
		return -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_DEF_MAX, nla, simple_policy,
					  NULL);
	if (err < 0)
		return err;

	if (tb[TCA_DEF_PARMS] == NULL)
		return -EINVAL;

	parm = nla_data(tb[TCA_DEF_PARMS]);
	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	if (err < 0)
		return err;
	exists = err;
	if (exists && bind)
		return 0;

	if (tb[TCA_DEF_DATA] == NULL) {
		if (exists)
			tcf_idr_release(*a, bind);
		else
			tcf_idr_cleanup(tn, index);
		return -EINVAL;
	}

	if (!exists) {
		ret = tcf_idr_create(tn, index, est, a,
				     &act_simp_ops, bind, false);
		if (ret) {
			tcf_idr_cleanup(tn, index);
			return ret;
		}

		d = to_defact(*a);
		err = tcf_action_check_ctrlact(parm->action, tp, &goto_ch,
					       extack);
		if (err < 0)
			goto release_idr;

		err = alloc_defdata(d, tb[TCA_DEF_DATA]);
		if (err < 0)
			goto put_chain;

		tcf_action_set_ctrlact(*a, parm->action, goto_ch);
		ret = ACT_P_CREATED;
	} else {
		if (!ovr) {
			err = -EEXIST;
			goto release_idr;
		}

		err = reset_policy(*a, tb[TCA_DEF_DATA], parm, tp, extack);
		if (err)
			goto release_idr;
	}

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