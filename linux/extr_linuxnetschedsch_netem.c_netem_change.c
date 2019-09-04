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
struct tc_netem_qopt {int /*<<< orphan*/  duplicate; int /*<<< orphan*/  loss; scalar_t__ gap; int /*<<< orphan*/  limit; int /*<<< orphan*/  jitter; int /*<<< orphan*/  latency; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct clgstate {int dummy; } ;
struct netem_sched_data {int loss_model; struct clgstate clg; int /*<<< orphan*/  ecn; void* jitter; void* latency; int /*<<< orphan*/  rate; int /*<<< orphan*/  reorder; scalar_t__ gap; int /*<<< orphan*/  duplicate; int /*<<< orphan*/  loss; scalar_t__ counter; int /*<<< orphan*/  limit; int /*<<< orphan*/  slot_dist; int /*<<< orphan*/  delay_dist; } ;
struct Qdisc {int /*<<< orphan*/  limit; } ;

/* Variables and functions */
 void* CLG_RANDOM ; 
 int EINVAL ; 
 void* PSCHED_TICKS2NS (int /*<<< orphan*/ ) ; 
 size_t TCA_NETEM_CORR ; 
 size_t TCA_NETEM_CORRUPT ; 
 size_t TCA_NETEM_DELAY_DIST ; 
 size_t TCA_NETEM_ECN ; 
 size_t TCA_NETEM_JITTER64 ; 
 size_t TCA_NETEM_LATENCY64 ; 
 size_t TCA_NETEM_LOSS ; 
 int /*<<< orphan*/  TCA_NETEM_MAX ; 
 size_t TCA_NETEM_RATE ; 
 size_t TCA_NETEM_RATE64 ; 
 size_t TCA_NETEM_REORDER ; 
 size_t TCA_NETEM_SLOT ; 
 size_t TCA_NETEM_SLOT_DIST ; 
 int /*<<< orphan*/  get_correlation (struct netem_sched_data*,struct nlattr*) ; 
 int /*<<< orphan*/  get_corrupt (struct netem_sched_data*,struct nlattr*) ; 
 int get_dist_table (struct Qdisc*,int /*<<< orphan*/ *,struct nlattr*) ; 
 int get_loss_clg (struct netem_sched_data*,struct nlattr*) ; 
 int /*<<< orphan*/  get_rate (struct netem_sched_data*,struct nlattr*) ; 
 int /*<<< orphan*/  get_reorder (struct netem_sched_data*,struct nlattr*) ; 
 int /*<<< orphan*/  get_slot (struct netem_sched_data*,struct nlattr*) ; 
 int /*<<< orphan*/  max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netem_policy ; 
 struct tc_netem_qopt* nla_data (struct nlattr*) ; 
 void* nla_get_s64 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u64 (struct nlattr*) ; 
 int parse_attr (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int) ; 
 struct netem_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  u64 ; 

__attribute__((used)) static int netem_change(struct Qdisc *sch, struct nlattr *opt,
			struct netlink_ext_ack *extack)
{
	struct netem_sched_data *q = qdisc_priv(sch);
	struct nlattr *tb[TCA_NETEM_MAX + 1];
	struct tc_netem_qopt *qopt;
	struct clgstate old_clg;
	int old_loss_model = CLG_RANDOM;
	int ret;

	if (opt == NULL)
		return -EINVAL;

	qopt = nla_data(opt);
	ret = parse_attr(tb, TCA_NETEM_MAX, opt, netem_policy, sizeof(*qopt));
	if (ret < 0)
		return ret;

	/* backup q->clg and q->loss_model */
	old_clg = q->clg;
	old_loss_model = q->loss_model;

	if (tb[TCA_NETEM_LOSS]) {
		ret = get_loss_clg(q, tb[TCA_NETEM_LOSS]);
		if (ret) {
			q->loss_model = old_loss_model;
			return ret;
		}
	} else {
		q->loss_model = CLG_RANDOM;
	}

	if (tb[TCA_NETEM_DELAY_DIST]) {
		ret = get_dist_table(sch, &q->delay_dist,
				     tb[TCA_NETEM_DELAY_DIST]);
		if (ret)
			goto get_table_failure;
	}

	if (tb[TCA_NETEM_SLOT_DIST]) {
		ret = get_dist_table(sch, &q->slot_dist,
				     tb[TCA_NETEM_SLOT_DIST]);
		if (ret)
			goto get_table_failure;
	}

	sch->limit = qopt->limit;

	q->latency = PSCHED_TICKS2NS(qopt->latency);
	q->jitter = PSCHED_TICKS2NS(qopt->jitter);
	q->limit = qopt->limit;
	q->gap = qopt->gap;
	q->counter = 0;
	q->loss = qopt->loss;
	q->duplicate = qopt->duplicate;

	/* for compatibility with earlier versions.
	 * if gap is set, need to assume 100% probability
	 */
	if (q->gap)
		q->reorder = ~0;

	if (tb[TCA_NETEM_CORR])
		get_correlation(q, tb[TCA_NETEM_CORR]);

	if (tb[TCA_NETEM_REORDER])
		get_reorder(q, tb[TCA_NETEM_REORDER]);

	if (tb[TCA_NETEM_CORRUPT])
		get_corrupt(q, tb[TCA_NETEM_CORRUPT]);

	if (tb[TCA_NETEM_RATE])
		get_rate(q, tb[TCA_NETEM_RATE]);

	if (tb[TCA_NETEM_RATE64])
		q->rate = max_t(u64, q->rate,
				nla_get_u64(tb[TCA_NETEM_RATE64]));

	if (tb[TCA_NETEM_LATENCY64])
		q->latency = nla_get_s64(tb[TCA_NETEM_LATENCY64]);

	if (tb[TCA_NETEM_JITTER64])
		q->jitter = nla_get_s64(tb[TCA_NETEM_JITTER64]);

	if (tb[TCA_NETEM_ECN])
		q->ecn = nla_get_u32(tb[TCA_NETEM_ECN]);

	if (tb[TCA_NETEM_SLOT])
		get_slot(q, tb[TCA_NETEM_SLOT]);

	return ret;

get_table_failure:
	/* recover clg and loss_model, in case of
	 * q->clg and q->loss_model were modified
	 * in get_loss_clg()
	 */
	q->clg = old_clg;
	q->loss_model = old_loss_model;
	return ret;
}