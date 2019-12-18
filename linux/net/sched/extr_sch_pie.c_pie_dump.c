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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int alpha; int beta; int ecn; int bytemode; int /*<<< orphan*/  tupdate; int /*<<< orphan*/  target; } ;
struct pie_sched_data {TYPE_1__ params; } ;
struct nlattr {int dummy; } ;
struct Qdisc {int limit; } ;

/* Variables and functions */
 int NSEC_PER_USEC ; 
 scalar_t__ PSCHED_TICKS2NS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  TCA_PIE_ALPHA ; 
 int /*<<< orphan*/  TCA_PIE_BETA ; 
 int /*<<< orphan*/  TCA_PIE_BYTEMODE ; 
 int /*<<< orphan*/  TCA_PIE_ECN ; 
 int /*<<< orphan*/  TCA_PIE_LIMIT ; 
 int /*<<< orphan*/  TCA_PIE_TARGET ; 
 int /*<<< orphan*/  TCA_PIE_TUPDATE ; 
 int jiffies_to_usecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct pie_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int pie_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	struct pie_sched_data *q = qdisc_priv(sch);
	struct nlattr *opts;

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	if (!opts)
		goto nla_put_failure;

	/* convert target from pschedtime to us */
	if (nla_put_u32(skb, TCA_PIE_TARGET,
			((u32)PSCHED_TICKS2NS(q->params.target)) /
			NSEC_PER_USEC) ||
	    nla_put_u32(skb, TCA_PIE_LIMIT, sch->limit) ||
	    nla_put_u32(skb, TCA_PIE_TUPDATE,
			jiffies_to_usecs(q->params.tupdate)) ||
	    nla_put_u32(skb, TCA_PIE_ALPHA, q->params.alpha) ||
	    nla_put_u32(skb, TCA_PIE_BETA, q->params.beta) ||
	    nla_put_u32(skb, TCA_PIE_ECN, q->params.ecn) ||
	    nla_put_u32(skb, TCA_PIE_BYTEMODE, q->params.bytemode))
		goto nla_put_failure;

	return nla_nest_end(skb, opts);

nla_put_failure:
	nla_nest_cancel(skb, opts);
	return -1;
}