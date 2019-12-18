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
typedef  int u64 ;
typedef  void* u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {void* bytemode; void* ecn; void* beta; void* alpha; void* limit; int /*<<< orphan*/  tupdate; int /*<<< orphan*/  target; } ;
struct pie_sched_data {TYPE_1__ params; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_4__ {unsigned int qlen; } ;
struct Qdisc {unsigned int limit; TYPE_2__ q; } ;

/* Variables and functions */
 int EINVAL ; 
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  PSCHED_NS2TICKS (int) ; 
 size_t TCA_PIE_ALPHA ; 
 size_t TCA_PIE_BETA ; 
 size_t TCA_PIE_BYTEMODE ; 
 size_t TCA_PIE_ECN ; 
 size_t TCA_PIE_LIMIT ; 
 int /*<<< orphan*/  TCA_PIE_MAX ; 
 size_t TCA_PIE_TARGET ; 
 size_t TCA_PIE_TUPDATE ; 
 struct sk_buff* __qdisc_dequeue_head (TYPE_2__*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pie_policy ; 
 scalar_t__ qdisc_pkt_len (struct sk_buff*) ; 
 struct pie_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_dec (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_tree_reduce_backlog (struct Qdisc*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rtnl_qdisc_drop (struct sk_buff*,struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 
 int /*<<< orphan*/  usecs_to_jiffies (void*) ; 

__attribute__((used)) static int pie_change(struct Qdisc *sch, struct nlattr *opt,
		      struct netlink_ext_ack *extack)
{
	struct pie_sched_data *q = qdisc_priv(sch);
	struct nlattr *tb[TCA_PIE_MAX + 1];
	unsigned int qlen, dropped = 0;
	int err;

	if (!opt)
		return -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_PIE_MAX, opt, pie_policy,
					  NULL);
	if (err < 0)
		return err;

	sch_tree_lock(sch);

	/* convert from microseconds to pschedtime */
	if (tb[TCA_PIE_TARGET]) {
		/* target is in us */
		u32 target = nla_get_u32(tb[TCA_PIE_TARGET]);

		/* convert to pschedtime */
		q->params.target = PSCHED_NS2TICKS((u64)target * NSEC_PER_USEC);
	}

	/* tupdate is in jiffies */
	if (tb[TCA_PIE_TUPDATE])
		q->params.tupdate =
			usecs_to_jiffies(nla_get_u32(tb[TCA_PIE_TUPDATE]));

	if (tb[TCA_PIE_LIMIT]) {
		u32 limit = nla_get_u32(tb[TCA_PIE_LIMIT]);

		q->params.limit = limit;
		sch->limit = limit;
	}

	if (tb[TCA_PIE_ALPHA])
		q->params.alpha = nla_get_u32(tb[TCA_PIE_ALPHA]);

	if (tb[TCA_PIE_BETA])
		q->params.beta = nla_get_u32(tb[TCA_PIE_BETA]);

	if (tb[TCA_PIE_ECN])
		q->params.ecn = nla_get_u32(tb[TCA_PIE_ECN]);

	if (tb[TCA_PIE_BYTEMODE])
		q->params.bytemode = nla_get_u32(tb[TCA_PIE_BYTEMODE]);

	/* Drop excess packets if new limit is lower */
	qlen = sch->q.qlen;
	while (sch->q.qlen > sch->limit) {
		struct sk_buff *skb = __qdisc_dequeue_head(&sch->q);

		dropped += qdisc_pkt_len(skb);
		qdisc_qstats_backlog_dec(sch, skb);
		rtnl_qdisc_drop(skb, sch);
	}
	qdisc_tree_reduce_backlog(sch, qlen - sch->q.qlen, dropped);

	sch_tree_unlock(sch);
	return 0;
}