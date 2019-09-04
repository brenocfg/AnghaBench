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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct fq_sched_data {int /*<<< orphan*/  fq_trees_log; int /*<<< orphan*/  low_rate_threshold; int /*<<< orphan*/  orphan_mask; int /*<<< orphan*/  flow_refill_delay; int /*<<< orphan*/  flow_max_rate; int /*<<< orphan*/  rate_enable; int /*<<< orphan*/  initial_quantum; int /*<<< orphan*/  quantum; int /*<<< orphan*/  flow_plimit; } ;
struct Qdisc {int /*<<< orphan*/  limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_FQ_BUCKETS_LOG ; 
 int /*<<< orphan*/  TCA_FQ_FLOW_MAX_RATE ; 
 int /*<<< orphan*/  TCA_FQ_FLOW_PLIMIT ; 
 int /*<<< orphan*/  TCA_FQ_FLOW_REFILL_DELAY ; 
 int /*<<< orphan*/  TCA_FQ_INITIAL_QUANTUM ; 
 int /*<<< orphan*/  TCA_FQ_LOW_RATE_THRESHOLD ; 
 int /*<<< orphan*/  TCA_FQ_ORPHAN_MASK ; 
 int /*<<< orphan*/  TCA_FQ_PLIMIT ; 
 int /*<<< orphan*/  TCA_FQ_QUANTUM ; 
 int /*<<< orphan*/  TCA_FQ_RATE_ENABLE ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  jiffies_to_usecs (int /*<<< orphan*/ ) ; 
 int nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fq_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int fq_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	struct fq_sched_data *q = qdisc_priv(sch);
	struct nlattr *opts;

	opts = nla_nest_start(skb, TCA_OPTIONS);
	if (opts == NULL)
		goto nla_put_failure;

	/* TCA_FQ_FLOW_DEFAULT_RATE is not used anymore */

	if (nla_put_u32(skb, TCA_FQ_PLIMIT, sch->limit) ||
	    nla_put_u32(skb, TCA_FQ_FLOW_PLIMIT, q->flow_plimit) ||
	    nla_put_u32(skb, TCA_FQ_QUANTUM, q->quantum) ||
	    nla_put_u32(skb, TCA_FQ_INITIAL_QUANTUM, q->initial_quantum) ||
	    nla_put_u32(skb, TCA_FQ_RATE_ENABLE, q->rate_enable) ||
	    nla_put_u32(skb, TCA_FQ_FLOW_MAX_RATE, q->flow_max_rate) ||
	    nla_put_u32(skb, TCA_FQ_FLOW_REFILL_DELAY,
			jiffies_to_usecs(q->flow_refill_delay)) ||
	    nla_put_u32(skb, TCA_FQ_ORPHAN_MASK, q->orphan_mask) ||
	    nla_put_u32(skb, TCA_FQ_LOW_RATE_THRESHOLD,
			q->low_rate_threshold) ||
	    nla_put_u32(skb, TCA_FQ_BUCKETS_LOG, q->fq_trees_log))
		goto nla_put_failure;

	return nla_nest_end(skb, opts);

nla_put_failure:
	return -1;
}