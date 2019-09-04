#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tcf_police {int tcfp_mtu; int rate_present; int peak_present; int /*<<< orphan*/  tcfp_t_c; int /*<<< orphan*/  tcf_lock; void* tcfp_ewma_rate; int /*<<< orphan*/  tcf_action; scalar_t__ tcfp_mtu_ptoks; scalar_t__ tcfp_ptoks; int /*<<< orphan*/  peak; int /*<<< orphan*/  tcfp_burst; int /*<<< orphan*/  tcfp_toks; void* tcfp_result; int /*<<< orphan*/  rate; int /*<<< orphan*/  tcf_rate_est; int /*<<< orphan*/  tcf_bstats; } ;
struct tc_police_compat {int dummy; } ;
struct TYPE_3__ {scalar_t__ rate; } ;
struct tc_police {int mtu; int /*<<< orphan*/  action; int /*<<< orphan*/  burst; TYPE_1__ peakrate; TYPE_1__ rate; int /*<<< orphan*/  index; } ;
struct tc_action_net {int dummy; } ;
struct tc_action {int dummy; } ;
struct TYPE_4__ {int cell_log; } ;
struct qdisc_rate_table {TYPE_2__ rate; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PSCHED_TICKS2NS (int /*<<< orphan*/ ) ; 
 size_t TCA_POLICE_AVRATE ; 
 int /*<<< orphan*/  TCA_POLICE_MAX ; 
 size_t TCA_POLICE_PEAKRATE ; 
 size_t TCA_POLICE_RATE ; 
 size_t TCA_POLICE_RESULT ; 
 size_t TCA_POLICE_TBF ; 
 int /*<<< orphan*/  act_police_ops ; 
 int /*<<< orphan*/  gen_estimator_active (int /*<<< orphan*/ *) ; 
 int gen_replace_estimator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nlattr*) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct tc_police* nla_data (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  police_net_id ; 
 int /*<<< orphan*/  police_policy ; 
 scalar_t__ psched_l2t_ns (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  psched_ratecfg_precompute (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct qdisc_rate_table* qdisc_get_rtab (TYPE_1__*,struct nlattr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_put_rtab (struct qdisc_rate_table*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tcf_idr_check_alloc (struct tc_action_net*,int /*<<< orphan*/ *,struct tc_action**,int) ; 
 int /*<<< orphan*/  tcf_idr_cleanup (struct tc_action_net*,int /*<<< orphan*/ ) ; 
 int tcf_idr_create (struct tc_action_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tc_action**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcf_idr_insert (struct tc_action_net*,struct tc_action*) ; 
 int /*<<< orphan*/  tcf_idr_release (struct tc_action*,int) ; 
 struct tcf_police* to_police (struct tc_action*) ; 

__attribute__((used)) static int tcf_police_init(struct net *net, struct nlattr *nla,
			       struct nlattr *est, struct tc_action **a,
			       int ovr, int bind, bool rtnl_held,
			       struct netlink_ext_ack *extack)
{
	int ret = 0, err;
	struct nlattr *tb[TCA_POLICE_MAX + 1];
	struct tc_police *parm;
	struct tcf_police *police;
	struct qdisc_rate_table *R_tab = NULL, *P_tab = NULL;
	struct tc_action_net *tn = net_generic(net, police_net_id);
	bool exists = false;
	int size;

	if (nla == NULL)
		return -EINVAL;

	err = nla_parse_nested(tb, TCA_POLICE_MAX, nla, police_policy, NULL);
	if (err < 0)
		return err;

	if (tb[TCA_POLICE_TBF] == NULL)
		return -EINVAL;
	size = nla_len(tb[TCA_POLICE_TBF]);
	if (size != sizeof(*parm) && size != sizeof(struct tc_police_compat))
		return -EINVAL;

	parm = nla_data(tb[TCA_POLICE_TBF]);
	err = tcf_idr_check_alloc(tn, &parm->index, a, bind);
	if (err < 0)
		return err;
	exists = err;
	if (exists && bind)
		return 0;

	if (!exists) {
		ret = tcf_idr_create(tn, parm->index, NULL, a,
				     &act_police_ops, bind, false);
		if (ret) {
			tcf_idr_cleanup(tn, parm->index);
			return ret;
		}
		ret = ACT_P_CREATED;
	} else if (!ovr) {
		tcf_idr_release(*a, bind);
		return -EEXIST;
	}

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
		err = gen_replace_estimator(&police->tcf_bstats, NULL,
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

	spin_lock_bh(&police->tcf_lock);
	/* No failure allowed after this point */
	police->tcfp_mtu = parm->mtu;
	if (police->tcfp_mtu == 0) {
		police->tcfp_mtu = ~0;
		if (R_tab)
			police->tcfp_mtu = 255 << R_tab->rate.cell_log;
	}
	if (R_tab) {
		police->rate_present = true;
		psched_ratecfg_precompute(&police->rate, &R_tab->rate, 0);
		qdisc_put_rtab(R_tab);
	} else {
		police->rate_present = false;
	}
	if (P_tab) {
		police->peak_present = true;
		psched_ratecfg_precompute(&police->peak, &P_tab->rate, 0);
		qdisc_put_rtab(P_tab);
	} else {
		police->peak_present = false;
	}

	if (tb[TCA_POLICE_RESULT])
		police->tcfp_result = nla_get_u32(tb[TCA_POLICE_RESULT]);
	police->tcfp_burst = PSCHED_TICKS2NS(parm->burst);
	police->tcfp_toks = police->tcfp_burst;
	if (police->peak_present) {
		police->tcfp_mtu_ptoks = (s64) psched_l2t_ns(&police->peak,
							     police->tcfp_mtu);
		police->tcfp_ptoks = police->tcfp_mtu_ptoks;
	}
	police->tcf_action = parm->action;

	if (tb[TCA_POLICE_AVRATE])
		police->tcfp_ewma_rate = nla_get_u32(tb[TCA_POLICE_AVRATE]);

	spin_unlock_bh(&police->tcf_lock);
	if (ret != ACT_P_CREATED)
		return ret;

	police->tcfp_t_c = ktime_get_ns();
	tcf_idr_insert(tn, *a);

	return ret;

failure:
	qdisc_put_rtab(P_tab);
	qdisc_put_rtab(R_tab);
	tcf_idr_release(*a, bind);
	return err;
}