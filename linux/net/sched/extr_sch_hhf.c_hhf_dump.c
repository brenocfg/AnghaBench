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
struct hhf_sched_data {int /*<<< orphan*/  hhf_non_hh_weight; int /*<<< orphan*/  hhf_evict_timeout; int /*<<< orphan*/  hhf_admit_bytes; int /*<<< orphan*/  hhf_reset_timeout; int /*<<< orphan*/  hh_flows_limit; int /*<<< orphan*/  quantum; } ;
struct Qdisc {int /*<<< orphan*/  limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_HHF_ADMIT_BYTES ; 
 int /*<<< orphan*/  TCA_HHF_BACKLOG_LIMIT ; 
 int /*<<< orphan*/  TCA_HHF_EVICT_TIMEOUT ; 
 int /*<<< orphan*/  TCA_HHF_HH_FLOWS_LIMIT ; 
 int /*<<< orphan*/  TCA_HHF_NON_HH_WEIGHT ; 
 int /*<<< orphan*/  TCA_HHF_QUANTUM ; 
 int /*<<< orphan*/  TCA_HHF_RESET_TIMEOUT ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  jiffies_to_usecs (int /*<<< orphan*/ ) ; 
 int nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hhf_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int hhf_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	struct hhf_sched_data *q = qdisc_priv(sch);
	struct nlattr *opts;

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	if (opts == NULL)
		goto nla_put_failure;

	if (nla_put_u32(skb, TCA_HHF_BACKLOG_LIMIT, sch->limit) ||
	    nla_put_u32(skb, TCA_HHF_QUANTUM, q->quantum) ||
	    nla_put_u32(skb, TCA_HHF_HH_FLOWS_LIMIT, q->hh_flows_limit) ||
	    nla_put_u32(skb, TCA_HHF_RESET_TIMEOUT,
			jiffies_to_usecs(q->hhf_reset_timeout)) ||
	    nla_put_u32(skb, TCA_HHF_ADMIT_BYTES, q->hhf_admit_bytes) ||
	    nla_put_u32(skb, TCA_HHF_EVICT_TIMEOUT,
			jiffies_to_usecs(q->hhf_evict_timeout)) ||
	    nla_put_u32(skb, TCA_HHF_NON_HH_WEIGHT, q->hhf_non_hh_weight))
		goto nla_put_failure;

	return nla_nest_end(skb, opts);

nla_put_failure:
	return -1;
}