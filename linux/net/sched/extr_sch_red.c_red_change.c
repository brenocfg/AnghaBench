#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tc_red_qopt {scalar_t__ limit; int flags; int /*<<< orphan*/  Scell_log; int /*<<< orphan*/  Plog; int /*<<< orphan*/  Wlog; int /*<<< orphan*/  qth_max; int /*<<< orphan*/  qth_min; } ;
struct red_sched_data {int flags; scalar_t__ limit; int /*<<< orphan*/  vars; struct Qdisc* qdisc; int /*<<< orphan*/  adapt_timer; int /*<<< orphan*/  parms; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_1__ q; } ;

/* Variables and functions */
 int EINVAL ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct Qdisc*) ; 
 int PTR_ERR (struct Qdisc*) ; 
 int /*<<< orphan*/  TCA_RED_MAX ; 
 size_t TCA_RED_MAX_P ; 
 size_t TCA_RED_PARMS ; 
 size_t TCA_RED_STAB ; 
 int TC_RED_ADAPTATIVE ; 
 int /*<<< orphan*/  bfifo_qdisc_ops ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 struct Qdisc* fifo_create_dflt (struct Qdisc*,int /*<<< orphan*/ *,scalar_t__,struct netlink_ext_ack*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct tc_red_qopt* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_hash_add (struct Qdisc*,int) ; 
 struct red_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_put (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_tree_flush_backlog (struct Qdisc*) ; 
 int /*<<< orphan*/  red_check_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  red_offload (struct Qdisc*,int) ; 
 int /*<<< orphan*/  red_policy ; 
 int /*<<< orphan*/  red_set_parms (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tc_red_qopt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  red_set_vars (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  red_start_of_idle_period (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int red_change(struct Qdisc *sch, struct nlattr *opt,
		      struct netlink_ext_ack *extack)
{
	struct Qdisc *old_child = NULL, *child = NULL;
	struct red_sched_data *q = qdisc_priv(sch);
	struct nlattr *tb[TCA_RED_MAX + 1];
	struct tc_red_qopt *ctl;
	int err;
	u32 max_P;

	if (opt == NULL)
		return -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_RED_MAX, opt, red_policy,
					  NULL);
	if (err < 0)
		return err;

	if (tb[TCA_RED_PARMS] == NULL ||
	    tb[TCA_RED_STAB] == NULL)
		return -EINVAL;

	max_P = tb[TCA_RED_MAX_P] ? nla_get_u32(tb[TCA_RED_MAX_P]) : 0;

	ctl = nla_data(tb[TCA_RED_PARMS]);
	if (!red_check_params(ctl->qth_min, ctl->qth_max, ctl->Wlog))
		return -EINVAL;

	if (ctl->limit > 0) {
		child = fifo_create_dflt(sch, &bfifo_qdisc_ops, ctl->limit,
					 extack);
		if (IS_ERR(child))
			return PTR_ERR(child);

		/* child is fifo, no need to check for noop_qdisc */
		qdisc_hash_add(child, true);
	}

	sch_tree_lock(sch);
	q->flags = ctl->flags;
	q->limit = ctl->limit;
	if (child) {
		qdisc_tree_flush_backlog(q->qdisc);
		old_child = q->qdisc;
		q->qdisc = child;
	}

	red_set_parms(&q->parms,
		      ctl->qth_min, ctl->qth_max, ctl->Wlog,
		      ctl->Plog, ctl->Scell_log,
		      nla_data(tb[TCA_RED_STAB]),
		      max_P);
	red_set_vars(&q->vars);

	del_timer(&q->adapt_timer);
	if (ctl->flags & TC_RED_ADAPTATIVE)
		mod_timer(&q->adapt_timer, jiffies + HZ/2);

	if (!q->qdisc->q.qlen)
		red_start_of_idle_period(&q->vars);

	sch_tree_unlock(sch);

	red_offload(sch, true);

	if (old_child)
		qdisc_put(old_child);
	return 0;
}