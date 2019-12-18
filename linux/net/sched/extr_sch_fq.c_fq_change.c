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
typedef  int u64 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct fq_sched_data {int fq_trees_log; int flow_plimit; int quantum; int initial_quantum; unsigned long flow_max_rate; int low_rate_threshold; int rate_enable; int orphan_mask; int ce_threshold; int /*<<< orphan*/  flow_refill_delay; } ;
struct TYPE_2__ {scalar_t__ qlen; } ;
struct Qdisc {int limit; TYPE_1__ q; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NSEC_PER_USEC ; 
 size_t TCA_FQ_BUCKETS_LOG ; 
 size_t TCA_FQ_CE_THRESHOLD ; 
 size_t TCA_FQ_FLOW_DEFAULT_RATE ; 
 size_t TCA_FQ_FLOW_MAX_RATE ; 
 size_t TCA_FQ_FLOW_PLIMIT ; 
 size_t TCA_FQ_FLOW_REFILL_DELAY ; 
 size_t TCA_FQ_INITIAL_QUANTUM ; 
 size_t TCA_FQ_LOW_RATE_THRESHOLD ; 
 int /*<<< orphan*/  TCA_FQ_MAX ; 
 size_t TCA_FQ_ORPHAN_MASK ; 
 size_t TCA_FQ_PLIMIT ; 
 size_t TCA_FQ_QUANTUM ; 
 size_t TCA_FQ_RATE_ENABLE ; 
 struct sk_buff* fq_dequeue (struct Qdisc*) ; 
 int /*<<< orphan*/  fq_policy ; 
 int fq_resize (struct Qdisc*,int) ; 
 int ilog2 (int) ; 
 int nla_get_u32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int) ; 
 scalar_t__ qdisc_pkt_len (struct sk_buff*) ; 
 struct fq_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_tree_reduce_backlog (struct Qdisc*,int,unsigned int) ; 
 int /*<<< orphan*/  rtnl_kfree_skbs (struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 

__attribute__((used)) static int fq_change(struct Qdisc *sch, struct nlattr *opt,
		     struct netlink_ext_ack *extack)
{
	struct fq_sched_data *q = qdisc_priv(sch);
	struct nlattr *tb[TCA_FQ_MAX + 1];
	int err, drop_count = 0;
	unsigned drop_len = 0;
	u32 fq_log;

	if (!opt)
		return -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_FQ_MAX, opt, fq_policy,
					  NULL);
	if (err < 0)
		return err;

	sch_tree_lock(sch);

	fq_log = q->fq_trees_log;

	if (tb[TCA_FQ_BUCKETS_LOG]) {
		u32 nval = nla_get_u32(tb[TCA_FQ_BUCKETS_LOG]);

		if (nval >= 1 && nval <= ilog2(256*1024))
			fq_log = nval;
		else
			err = -EINVAL;
	}
	if (tb[TCA_FQ_PLIMIT])
		sch->limit = nla_get_u32(tb[TCA_FQ_PLIMIT]);

	if (tb[TCA_FQ_FLOW_PLIMIT])
		q->flow_plimit = nla_get_u32(tb[TCA_FQ_FLOW_PLIMIT]);

	if (tb[TCA_FQ_QUANTUM]) {
		u32 quantum = nla_get_u32(tb[TCA_FQ_QUANTUM]);

		if (quantum > 0)
			q->quantum = quantum;
		else
			err = -EINVAL;
	}

	if (tb[TCA_FQ_INITIAL_QUANTUM])
		q->initial_quantum = nla_get_u32(tb[TCA_FQ_INITIAL_QUANTUM]);

	if (tb[TCA_FQ_FLOW_DEFAULT_RATE])
		pr_warn_ratelimited("sch_fq: defrate %u ignored.\n",
				    nla_get_u32(tb[TCA_FQ_FLOW_DEFAULT_RATE]));

	if (tb[TCA_FQ_FLOW_MAX_RATE]) {
		u32 rate = nla_get_u32(tb[TCA_FQ_FLOW_MAX_RATE]);

		q->flow_max_rate = (rate == ~0U) ? ~0UL : rate;
	}
	if (tb[TCA_FQ_LOW_RATE_THRESHOLD])
		q->low_rate_threshold =
			nla_get_u32(tb[TCA_FQ_LOW_RATE_THRESHOLD]);

	if (tb[TCA_FQ_RATE_ENABLE]) {
		u32 enable = nla_get_u32(tb[TCA_FQ_RATE_ENABLE]);

		if (enable <= 1)
			q->rate_enable = enable;
		else
			err = -EINVAL;
	}

	if (tb[TCA_FQ_FLOW_REFILL_DELAY]) {
		u32 usecs_delay = nla_get_u32(tb[TCA_FQ_FLOW_REFILL_DELAY]) ;

		q->flow_refill_delay = usecs_to_jiffies(usecs_delay);
	}

	if (tb[TCA_FQ_ORPHAN_MASK])
		q->orphan_mask = nla_get_u32(tb[TCA_FQ_ORPHAN_MASK]);

	if (tb[TCA_FQ_CE_THRESHOLD])
		q->ce_threshold = (u64)NSEC_PER_USEC *
				  nla_get_u32(tb[TCA_FQ_CE_THRESHOLD]);

	if (!err) {
		sch_tree_unlock(sch);
		err = fq_resize(sch, fq_log);
		sch_tree_lock(sch);
	}
	while (sch->q.qlen > sch->limit) {
		struct sk_buff *skb = fq_dequeue(sch);

		if (!skb)
			break;
		drop_len += qdisc_pkt_len(skb);
		rtnl_kfree_skbs(skb, skb);
		drop_count++;
	}
	qdisc_tree_reduce_backlog(sch, drop_count, drop_len);

	sch_tree_unlock(sch);
	return err;
}