#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tc_sfb_qopt {int /*<<< orphan*/  penalty_burst; int /*<<< orphan*/  penalty_rate; int /*<<< orphan*/  decrement; int /*<<< orphan*/  increment; int /*<<< orphan*/  bin_size; int /*<<< orphan*/  max; int /*<<< orphan*/  limit; int /*<<< orphan*/  warmup_time; int /*<<< orphan*/  rehash_interval; } ;
struct sk_buff {int dummy; } ;
struct sfb_sched_data {TYPE_3__* qdisc; int /*<<< orphan*/  penalty_burst; int /*<<< orphan*/  penalty_rate; int /*<<< orphan*/  decrement; int /*<<< orphan*/  increment; int /*<<< orphan*/  bin_size; int /*<<< orphan*/  max; int /*<<< orphan*/  limit; int /*<<< orphan*/  warmup_time; int /*<<< orphan*/  rehash_interval; } ;
struct nlattr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  backlog; } ;
struct Qdisc {TYPE_1__ qstats; } ;
typedef  int /*<<< orphan*/  opt ;
struct TYPE_5__ {int /*<<< orphan*/  backlog; } ;
struct TYPE_6__ {TYPE_2__ qstats; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  TCA_SFB_PARMS ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_sfb_qopt*) ; 
 struct sfb_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int sfb_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	struct sfb_sched_data *q = qdisc_priv(sch);
	struct nlattr *opts;
	struct tc_sfb_qopt opt = {
		.rehash_interval = jiffies_to_msecs(q->rehash_interval),
		.warmup_time = jiffies_to_msecs(q->warmup_time),
		.limit = q->limit,
		.max = q->max,
		.bin_size = q->bin_size,
		.increment = q->increment,
		.decrement = q->decrement,
		.penalty_rate = q->penalty_rate,
		.penalty_burst = q->penalty_burst,
	};

	sch->qstats.backlog = q->qdisc->qstats.backlog;
	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	if (opts == NULL)
		goto nla_put_failure;
	if (nla_put(skb, TCA_SFB_PARMS, sizeof(opt), &opt))
		goto nla_put_failure;
	return nla_nest_end(skb, opts);

nla_put_failure:
	nla_nest_cancel(skb, opts);
	return -EMSGSIZE;
}