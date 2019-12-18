#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct tcf_proto {int dummy; } ;
struct tcf_police_params {int tcfp_result; int tcfp_mtu; int rate_present; int peak_present; scalar_t__ tcfp_mtu_ptoks; int /*<<< orphan*/  tcfp_burst; void* tcfp_ewma_rate; int /*<<< orphan*/  peak; int /*<<< orphan*/  rate; } ;
struct TYPE_4__ {int /*<<< orphan*/  cpu_bstats; } ;
struct tcf_police {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  params; int /*<<< orphan*/  tcfp_lock; scalar_t__ tcfp_ptoks; int /*<<< orphan*/  tcfp_toks; int /*<<< orphan*/  tcfp_t_c; int /*<<< orphan*/  tcf_rate_est; TYPE_1__ common; int /*<<< orphan*/  tcf_bstats; } ;
struct tcf_chain {int dummy; } ;
struct tc_police_compat {int dummy; } ;
struct TYPE_5__ {scalar_t__ rate; } ;
struct tc_police {int mtu; int /*<<< orphan*/  action; int /*<<< orphan*/  burst; TYPE_2__ peakrate; TYPE_2__ rate; int /*<<< orphan*/  index; } ;
struct tc_action_net {int dummy; } ;
struct tc_action {int dummy; } ;
struct TYPE_6__ {int cell_log; } ;
struct qdisc_rate_table {TYPE_3__ rate; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  PSCHED_TICKS2NS (int /*<<< orphan*/ ) ; 
 size_t TCA_POLICE_AVRATE ; 
 int /*<<< orphan*/  TCA_POLICE_MAX ; 
 size_t TCA_POLICE_PEAKRATE ; 
 size_t TCA_POLICE_PEAKRATE64 ; 
 size_t TCA_POLICE_RATE ; 
 size_t TCA_POLICE_RATE64 ; 
 size_t TCA_POLICE_RESULT ; 
 size_t TCA_POLICE_TBF ; 
 scalar_t__ TC_ACT_EXT_CMP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TC_ACT_GOTO_CHAIN ; 
 int TC_ACT_OK ; 
 int /*<<< orphan*/  act_police_ops ; 
 int /*<<< orphan*/  gen_estimator_active (int /*<<< orphan*/ *) ; 
 int gen_replace_estimator (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nlattr*) ; 
 int /*<<< orphan*/  kfree_rcu (struct tcf_police_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 struct tcf_police_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct tc_police* nla_data (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u64 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  police_net_id ; 
 int /*<<< orphan*/  police_policy ; 
 scalar_t__ psched_l2t_ns (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  psched_ratecfg_precompute (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct qdisc_rate_table* qdisc_get_rtab (TYPE_2__*,struct nlattr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_put_rtab (struct qdisc_rate_table*) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_swap_protected (int /*<<< orphan*/ ,struct tcf_police_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tcf_action_check_ctrlact (int /*<<< orphan*/ ,struct tcf_proto*,struct tcf_chain**,struct netlink_ext_ack*) ; 
 struct tcf_chain* tcf_action_set_ctrlact (struct tc_action*,int /*<<< orphan*/ ,struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_put_by_act (struct tcf_chain*) ; 
 int tcf_idr_check_alloc (struct tc_action_net*,int /*<<< orphan*/ *,struct tc_action**,int) ; 
 int /*<<< orphan*/  tcf_idr_cleanup (struct tc_action_net*,int /*<<< orphan*/ ) ; 
 int tcf_idr_create (struct tc_action_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tc_action**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcf_idr_insert (struct tc_action_net*,struct tc_action*) ; 
 int /*<<< orphan*/  tcf_idr_release (struct tc_action*,int) ; 
 struct tcf_police* to_police (struct tc_action*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tcf_police_init(struct net *net, struct nlattr *nla,
			       struct nlattr *est, struct tc_action **a,
			       int ovr, int bind, bool rtnl_held,
			       struct tcf_proto *tp,
			       struct netlink_ext_ack *extack)
{
	int ret = 0, tcfp_result = TC_ACT_OK, err, size;
	struct nlattr *tb[TCA_POLICE_MAX + 1];
	struct tcf_chain *goto_ch = NULL;
	struct tc_police *parm;
	struct tcf_police *police;
	struct qdisc_rate_table *R_tab = NULL, *P_tab = NULL;
	struct tc_action_net *tn = net_generic(net, police_net_id);
	struct tcf_police_params *new;
	bool exists = false;
	u32 index;
	u64 rate64, prate64;

	if (nla == NULL)
		return -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_POLICE_MAX, nla,
					  police_policy, NULL);
	if (err < 0)
		return err;

	if (tb[TCA_POLICE_TBF] == NULL)
		return -EINVAL;
	size = nla_len(tb[TCA_POLICE_TBF]);
	if (size != sizeof(*parm) && size != sizeof(struct tc_police_compat))
		return -EINVAL;

	parm = nla_data(tb[TCA_POLICE_TBF]);
	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	if (err < 0)
		return err;
	exists = err;
	if (exists && bind)
		return 0;

	if (!exists) {
		ret = tcf_idr_create(tn, index, NULL, a,
				     &act_police_ops, bind, true);
		if (ret) {
			tcf_idr_cleanup(tn, index);
			return ret;
		}
		ret = ACT_P_CREATED;
		spin_lock_init(&(to_police(*a)->tcfp_lock));
	} else if (!ovr) {
		tcf_idr_release(*a, bind);
		return -EEXIST;
	}
	err = tcf_action_check_ctrlact(parm->action, tp, &goto_ch, extack);
	if (err < 0)
		goto release_idr;

	police = to_police(*a);
	if (parm->rate.rate) {
		err = -ENOMEM;
		R_tab = qdisc_get_rtab(&parm->rate, tb[TCA_POLICE_RATE], NULL);
		if (R_tab == NULL)
			goto failure;

		if (parm->peakrate.rate) {
			P_tab = qdisc_get_rtab(&parm->peakrate,
					       tb[TCA_POLICE_PEAKRATE], NULL);
			if (P_tab == NULL)
				goto failure;
		}
	}

	if (est) {
		err = gen_replace_estimator(&police->tcf_bstats,
					    police->common.cpu_bstats,
					    &police->tcf_rate_est,
					    &police->tcf_lock,
					    NULL, est);
		if (err)
			goto failure;
	} else if (tb[TCA_POLICE_AVRATE] &&
		   (ret == ACT_P_CREATED ||
		    !gen_estimator_active(&police->tcf_rate_est))) {
		err = -EINVAL;
		goto failure;
	}

	if (tb[TCA_POLICE_RESULT]) {
		tcfp_result = nla_get_u32(tb[TCA_POLICE_RESULT]);
		if (TC_ACT_EXT_CMP(tcfp_result, TC_ACT_GOTO_CHAIN)) {
			NL_SET_ERR_MSG(extack,
				       "goto chain not allowed on fallback");
			err = -EINVAL;
			goto failure;
		}
	}

	new = kzalloc(sizeof(*new), GFP_KERNEL);
	if (unlikely(!new)) {
		err = -ENOMEM;
		goto failure;
	}

	/* No failure allowed after this point */
	new->tcfp_result = tcfp_result;
	new->tcfp_mtu = parm->mtu;
	if (!new->tcfp_mtu) {
		new->tcfp_mtu = ~0;
		if (R_tab)
			new->tcfp_mtu = 255 << R_tab->rate.cell_log;
	}
	if (R_tab) {
		new->rate_present = true;
		rate64 = tb[TCA_POLICE_RATE64] ?
			 nla_get_u64(tb[TCA_POLICE_RATE64]) : 0;
		psched_ratecfg_precompute(&new->rate, &R_tab->rate, rate64);
		qdisc_put_rtab(R_tab);
	} else {
		new->rate_present = false;
	}
	if (P_tab) {
		new->peak_present = true;
		prate64 = tb[TCA_POLICE_PEAKRATE64] ?
			  nla_get_u64(tb[TCA_POLICE_PEAKRATE64]) : 0;
		psched_ratecfg_precompute(&new->peak, &P_tab->rate, prate64);
		qdisc_put_rtab(P_tab);
	} else {
		new->peak_present = false;
	}

	new->tcfp_burst = PSCHED_TICKS2NS(parm->burst);
	if (new->peak_present)
		new->tcfp_mtu_ptoks = (s64)psched_l2t_ns(&new->peak,
							 new->tcfp_mtu);

	if (tb[TCA_POLICE_AVRATE])
		new->tcfp_ewma_rate = nla_get_u32(tb[TCA_POLICE_AVRATE]);

	spin_lock_bh(&police->tcf_lock);
	spin_lock_bh(&police->tcfp_lock);
	police->tcfp_t_c = ktime_get_ns();
	police->tcfp_toks = new->tcfp_burst;
	if (new->peak_present)
		police->tcfp_ptoks = new->tcfp_mtu_ptoks;
	spin_unlock_bh(&police->tcfp_lock);
	goto_ch = tcf_action_set_ctrlact(*a, parm->action, goto_ch);
	rcu_swap_protected(police->params,
			   new,
			   lockdep_is_held(&police->tcf_lock));
	spin_unlock_bh(&police->tcf_lock);

	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
	if (new)
		kfree_rcu(new, rcu);

	if (ret == ACT_P_CREATED)
		tcf_idr_insert(tn, *a);
	return ret;

failure:
	qdisc_put_rtab(P_tab);
	qdisc_put_rtab(R_tab);
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
release_idr:
	tcf_idr_release(*a, bind);
	return err;
}