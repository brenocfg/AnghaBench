#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct tc_ratespec {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  classid; } ;
struct TYPE_13__ {int allot; int quantum; int avpkt; int minidle; TYPE_3__* R_tab; int /*<<< orphan*/  block; int /*<<< orphan*/  ewma_log; int /*<<< orphan*/  weight; void* cpriority; void* priority2; void* priority; int /*<<< orphan*/ * q; struct Qdisc* qdisc; TYPE_1__ common; struct TYPE_13__* sibling; int /*<<< orphan*/  filter_list; } ;
struct TYPE_12__ {int /*<<< orphan*/  function; } ;
struct cbq_sched_data {TYPE_6__ link; int /*<<< orphan*/  now; int /*<<< orphan*/  toplevel; int /*<<< orphan*/  clhash; TYPE_5__ delay_timer; int /*<<< orphan*/  watchdog; } ;
struct Qdisc {int /*<<< orphan*/  handle; int /*<<< orphan*/  dev_queue; } ;
struct TYPE_10__ {int /*<<< orphan*/  rate; } ;
struct TYPE_11__ {TYPE_2__ rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int EINVAL ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS_PINNED ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 size_t TCA_CBQ_LSSOPT ; 
 int /*<<< orphan*/  TCA_CBQ_MAX ; 
 size_t TCA_CBQ_RATE ; 
 size_t TCA_CBQ_RTAB ; 
 int /*<<< orphan*/  TC_CBQ_DEF_EWMA ; 
 int /*<<< orphan*/  TC_CBQ_MAXLEVEL ; 
 void* TC_CBQ_MAXPRIO ; 
 int /*<<< orphan*/  cbq_addprio (struct cbq_sched_data*,TYPE_6__*) ; 
 int /*<<< orphan*/  cbq_link_class (TYPE_6__*) ; 
 int cbq_opt_parse (struct nlattr**,struct nlattr*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  cbq_set_lss (TYPE_6__*,struct tc_ratespec*) ; 
 int /*<<< orphan*/  cbq_undelay ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tc_ratespec* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  noop_qdisc ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 int /*<<< orphan*/  psched_get_time () ; 
 int psched_mtu (int /*<<< orphan*/ ) ; 
 int qdisc_class_hash_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 TYPE_3__* qdisc_get_rtab (struct tc_ratespec*,struct nlattr*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  qdisc_hash_add (int /*<<< orphan*/ *,int) ; 
 struct cbq_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_put_rtab (TYPE_3__*) ; 
 int /*<<< orphan*/  qdisc_watchdog_init (int /*<<< orphan*/ *,struct Qdisc*) ; 
 int tcf_block_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct Qdisc*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  tcf_block_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cbq_init(struct Qdisc *sch, struct nlattr *opt,
		    struct netlink_ext_ack *extack)
{
	struct cbq_sched_data *q = qdisc_priv(sch);
	struct nlattr *tb[TCA_CBQ_MAX + 1];
	struct tc_ratespec *r;
	int err;

	qdisc_watchdog_init(&q->watchdog, sch);
	hrtimer_init(&q->delay_timer, CLOCK_MONOTONIC, HRTIMER_MODE_ABS_PINNED);
	q->delay_timer.function = cbq_undelay;

	err = cbq_opt_parse(tb, opt, extack);
	if (err < 0)
		return err;

	if (!tb[TCA_CBQ_RTAB] || !tb[TCA_CBQ_RATE]) {
		NL_SET_ERR_MSG(extack, "Rate specification missing or incomplete");
		return -EINVAL;
	}

	r = nla_data(tb[TCA_CBQ_RATE]);

	q->link.R_tab = qdisc_get_rtab(r, tb[TCA_CBQ_RTAB], extack);
	if (!q->link.R_tab)
		return -EINVAL;

	err = tcf_block_get(&q->link.block, &q->link.filter_list, sch, extack);
	if (err)
		goto put_rtab;

	err = qdisc_class_hash_init(&q->clhash);
	if (err < 0)
		goto put_block;

	q->link.sibling = &q->link;
	q->link.common.classid = sch->handle;
	q->link.qdisc = sch;
	q->link.q = qdisc_create_dflt(sch->dev_queue, &pfifo_qdisc_ops,
				      sch->handle, NULL);
	if (!q->link.q)
		q->link.q = &noop_qdisc;
	else
		qdisc_hash_add(q->link.q, true);

	q->link.priority = TC_CBQ_MAXPRIO - 1;
	q->link.priority2 = TC_CBQ_MAXPRIO - 1;
	q->link.cpriority = TC_CBQ_MAXPRIO - 1;
	q->link.allot = psched_mtu(qdisc_dev(sch));
	q->link.quantum = q->link.allot;
	q->link.weight = q->link.R_tab->rate.rate;

	q->link.ewma_log = TC_CBQ_DEF_EWMA;
	q->link.avpkt = q->link.allot/2;
	q->link.minidle = -0x7FFFFFFF;

	q->toplevel = TC_CBQ_MAXLEVEL;
	q->now = psched_get_time();

	cbq_link_class(&q->link);

	if (tb[TCA_CBQ_LSSOPT])
		cbq_set_lss(&q->link, nla_data(tb[TCA_CBQ_LSSOPT]));

	cbq_addprio(q, &q->link);
	return 0;

put_block:
	tcf_block_put(q->link.block);

put_rtab:
	qdisc_put_rtab(q->link.R_tab);
	return err;
}