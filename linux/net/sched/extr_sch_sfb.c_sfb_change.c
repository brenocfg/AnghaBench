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
typedef  scalar_t__ u32 ;
struct tc_sfb_qopt {scalar_t__ limit; int /*<<< orphan*/  penalty_burst; int /*<<< orphan*/  penalty_rate; int /*<<< orphan*/  bin_size; int /*<<< orphan*/  max; int /*<<< orphan*/  decrement; int /*<<< orphan*/  increment; int /*<<< orphan*/  warmup_time; int /*<<< orphan*/  rehash_interval; } ;
struct sfb_sched_data {int double_buffering; scalar_t__ slot; void* token_time; int /*<<< orphan*/  tokens_avail; int /*<<< orphan*/  penalty_burst; int /*<<< orphan*/  penalty_rate; int /*<<< orphan*/  bin_size; int /*<<< orphan*/  max; int /*<<< orphan*/  decrement; int /*<<< orphan*/  increment; scalar_t__ limit; void* rehash_time; void* warmup_time; void* rehash_interval; struct Qdisc* qdisc; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct Qdisc {int dummy; } ;
struct TYPE_2__ {scalar_t__ tx_queue_len; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct Qdisc*) ; 
 int PTR_ERR (struct Qdisc*) ; 
 int /*<<< orphan*/  TCA_SFB_MAX ; 
 size_t TCA_SFB_PARMS ; 
 struct Qdisc* fifo_create_dflt (struct Qdisc*,int /*<<< orphan*/ *,scalar_t__,struct netlink_ext_ack*) ; 
 void* jiffies ; 
 void* msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct tc_sfb_qopt* nla_data (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct Qdisc noop_qdisc ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 TYPE_1__* qdisc_dev (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_hash_add (struct Qdisc*,int) ; 
 struct sfb_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_purge_queue (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_put (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 
 struct tc_sfb_qopt sfb_default_ops ; 
 int /*<<< orphan*/  sfb_init_perturbation (int,struct sfb_sched_data*) ; 
 int /*<<< orphan*/  sfb_policy ; 
 int /*<<< orphan*/  sfb_zero_all_buckets (struct sfb_sched_data*) ; 

__attribute__((used)) static int sfb_change(struct Qdisc *sch, struct nlattr *opt,
		      struct netlink_ext_ack *extack)
{
	struct sfb_sched_data *q = qdisc_priv(sch);
	struct Qdisc *child, *old;
	struct nlattr *tb[TCA_SFB_MAX + 1];
	const struct tc_sfb_qopt *ctl = &sfb_default_ops;
	u32 limit;
	int err;

	if (opt) {
		err = nla_parse_nested_deprecated(tb, TCA_SFB_MAX, opt,
						  sfb_policy, NULL);
		if (err < 0)
			return -EINVAL;

		if (tb[TCA_SFB_PARMS] == NULL)
			return -EINVAL;

		ctl = nla_data(tb[TCA_SFB_PARMS]);
	}

	limit = ctl->limit;
	if (limit == 0)
		limit = qdisc_dev(sch)->tx_queue_len;

	child = fifo_create_dflt(sch, &pfifo_qdisc_ops, limit, extack);
	if (IS_ERR(child))
		return PTR_ERR(child);

	if (child != &noop_qdisc)
		qdisc_hash_add(child, true);
	sch_tree_lock(sch);

	qdisc_purge_queue(q->qdisc);
	old = q->qdisc;
	q->qdisc = child;

	q->rehash_interval = msecs_to_jiffies(ctl->rehash_interval);
	q->warmup_time = msecs_to_jiffies(ctl->warmup_time);
	q->rehash_time = jiffies;
	q->limit = limit;
	q->increment = ctl->increment;
	q->decrement = ctl->decrement;
	q->max = ctl->max;
	q->bin_size = ctl->bin_size;
	q->penalty_rate = ctl->penalty_rate;
	q->penalty_burst = ctl->penalty_burst;
	q->tokens_avail = ctl->penalty_burst;
	q->token_time = jiffies;

	q->slot = 0;
	q->double_buffering = false;
	sfb_zero_all_buckets(q);
	sfb_init_perturbation(0, q);
	sfb_init_perturbation(1, q);

	sch_tree_unlock(sch);
	qdisc_put(old);

	return 0;
}