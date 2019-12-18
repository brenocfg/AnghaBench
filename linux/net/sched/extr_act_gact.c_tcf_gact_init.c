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
struct tcf_gact {scalar_t__ tcfg_ptype; int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcfg_pval; int /*<<< orphan*/  tcfg_paction; } ;
struct tcf_chain {int dummy; } ;
struct tc_gact_p {scalar_t__ ptype; int /*<<< orphan*/  pval; int /*<<< orphan*/  paction; } ;
struct tc_gact {int /*<<< orphan*/  action; int /*<<< orphan*/  index; } ;
struct tc_action_net {int dummy; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EEXIST ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ MAX_RAND ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  TCA_GACT_MAX ; 
 size_t TCA_GACT_PARMS ; 
 size_t TCA_GACT_PROB ; 
 scalar_t__ TC_ACT_EXT_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TC_ACT_GOTO_CHAIN ; 
 int /*<<< orphan*/  act_gact_ops ; 
 int /*<<< orphan*/  gact_net_id ; 
 int /*<<< orphan*/  gact_policy ; 
 int /*<<< orphan*/  max_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 void* nla_data (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
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
 struct tcf_gact* to_gact (struct tc_action*) ; 
 int /*<<< orphan*/  u16 ; 

__attribute__((used)) static int tcf_gact_init(struct net *net, struct nlattr *nla,
			 struct nlattr *est, struct tc_action **a,
			 int ovr, int bind, bool rtnl_held,
			 struct tcf_proto *tp, struct netlink_ext_ack *extack)
{
	struct tc_action_net *tn = net_generic(net, gact_net_id);
	struct nlattr *tb[TCA_GACT_MAX + 1];
	struct tcf_chain *goto_ch = NULL;
	struct tc_gact *parm;
	struct tcf_gact *gact;
	int ret = 0;
	u32 index;
	int err;
#ifdef CONFIG_GACT_PROB
	struct tc_gact_p *p_parm = NULL;
#endif

	if (nla == NULL)
		return -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_GACT_MAX, nla, gact_policy,
					  NULL);
	if (err < 0)
		return err;

	if (tb[TCA_GACT_PARMS] == NULL)
		return -EINVAL;
	parm = nla_data(tb[TCA_GACT_PARMS]);
	index = parm->index;

#ifndef CONFIG_GACT_PROB
	if (tb[TCA_GACT_PROB] != NULL)
		return -EOPNOTSUPP;
#else
	if (tb[TCA_GACT_PROB]) {
		p_parm = nla_data(tb[TCA_GACT_PROB]);
		if (p_parm->ptype >= MAX_RAND)
			return -EINVAL;
		if (TC_ACT_EXT_CMP(p_parm->paction, TC_ACT_GOTO_CHAIN)) {
			NL_SET_ERR_MSG(extack,
				       "goto chain not allowed on fallback");
			return -EINVAL;
		}
	}
#endif

	err = tcf_idr_check_alloc(tn, &index, a, bind);
	if (!err) {
		ret = tcf_idr_create(tn, index, est, a,
				     &act_gact_ops, bind, true);
		if (ret) {
			tcf_idr_cleanup(tn, index);
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

	err = tcf_action_check_ctrlact(parm->action, tp, &goto_ch, extack);
	if (err < 0)
		goto release_idr;
	gact = to_gact(*a);

	spin_lock_bh(&gact->tcf_lock);
	goto_ch = tcf_action_set_ctrlact(*a, parm->action, goto_ch);
#ifdef CONFIG_GACT_PROB
	if (p_parm) {
		gact->tcfg_paction = p_parm->paction;
		gact->tcfg_pval    = max_t(u16, 1, p_parm->pval);
		/* Make sure tcfg_pval is written before tcfg_ptype
		 * coupled with smp_rmb() in gact_net_rand() & gact_determ()
		 */
		smp_wmb();
		gact->tcfg_ptype   = p_parm->ptype;
	}
#endif
	spin_unlock_bh(&gact->tcf_lock);

	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);

	if (ret == ACT_P_CREATED)
		tcf_idr_insert(tn, *a);
	return ret;
release_idr:
	tcf_idr_release(*a, bind);
	return err;
}