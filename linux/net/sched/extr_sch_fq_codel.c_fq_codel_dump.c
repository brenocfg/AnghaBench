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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {scalar_t__ target; scalar_t__ interval; scalar_t__ ce_threshold; int /*<<< orphan*/  ecn; } ;
struct fq_codel_sched_data {TYPE_1__ cparams; int /*<<< orphan*/  flows_cnt; int /*<<< orphan*/  memory_limit; int /*<<< orphan*/  drop_batch_size; int /*<<< orphan*/  quantum; } ;
struct Qdisc {int /*<<< orphan*/  limit; } ;

/* Variables and functions */
 scalar_t__ CODEL_DISABLED_THRESHOLD ; 
 int /*<<< orphan*/  TCA_FQ_CODEL_CE_THRESHOLD ; 
 int /*<<< orphan*/  TCA_FQ_CODEL_DROP_BATCH_SIZE ; 
 int /*<<< orphan*/  TCA_FQ_CODEL_ECN ; 
 int /*<<< orphan*/  TCA_FQ_CODEL_FLOWS ; 
 int /*<<< orphan*/  TCA_FQ_CODEL_INTERVAL ; 
 int /*<<< orphan*/  TCA_FQ_CODEL_LIMIT ; 
 int /*<<< orphan*/  TCA_FQ_CODEL_MEMORY_LIMIT ; 
 int /*<<< orphan*/  TCA_FQ_CODEL_QUANTUM ; 
 int /*<<< orphan*/  TCA_FQ_CODEL_TARGET ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  codel_time_to_us (scalar_t__) ; 
 int nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fq_codel_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int fq_codel_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	struct fq_codel_sched_data *q = qdisc_priv(sch);
	struct nlattr *opts;

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	if (opts == NULL)
		goto nla_put_failure;

	if (nla_put_u32(skb, TCA_FQ_CODEL_TARGET,
			codel_time_to_us(q->cparams.target)) ||
	    nla_put_u32(skb, TCA_FQ_CODEL_LIMIT,
			sch->limit) ||
	    nla_put_u32(skb, TCA_FQ_CODEL_INTERVAL,
			codel_time_to_us(q->cparams.interval)) ||
	    nla_put_u32(skb, TCA_FQ_CODEL_ECN,
			q->cparams.ecn) ||
	    nla_put_u32(skb, TCA_FQ_CODEL_QUANTUM,
			q->quantum) ||
	    nla_put_u32(skb, TCA_FQ_CODEL_DROP_BATCH_SIZE,
			q->drop_batch_size) ||
	    nla_put_u32(skb, TCA_FQ_CODEL_MEMORY_LIMIT,
			q->memory_limit) ||
	    nla_put_u32(skb, TCA_FQ_CODEL_FLOWS,
			q->flows_cnt))
		goto nla_put_failure;

	if (q->cparams.ce_threshold != CODEL_DISABLED_THRESHOLD &&
	    nla_put_u32(skb, TCA_FQ_CODEL_CE_THRESHOLD,
			codel_time_to_us(q->cparams.ce_threshold)))
		goto nla_put_failure;

	return nla_nest_end(skb, opts);

nla_put_failure:
	return -1;
}