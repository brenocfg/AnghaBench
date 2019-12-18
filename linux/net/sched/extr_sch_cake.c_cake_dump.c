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
struct cake_sched_data {int flow_mode; int interval; int target; int buffer_config_limit; int rate_flags; int ack_filter; int tin_mode; int rate_overhead; int atm_mode; int rate_mpu; int fwmark_mask; int /*<<< orphan*/  rate_bps; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int CAKE_FLAG_AUTORATE_INGRESS ; 
 int CAKE_FLAG_INGRESS ; 
 int CAKE_FLAG_OVERHEAD ; 
 int CAKE_FLAG_SPLIT_GSO ; 
 int CAKE_FLAG_WASH ; 
 int CAKE_FLOW_MASK ; 
 int CAKE_FLOW_NAT_FLAG ; 
 int /*<<< orphan*/  TCA_CAKE_ACK_FILTER ; 
 int /*<<< orphan*/  TCA_CAKE_ATM ; 
 int /*<<< orphan*/  TCA_CAKE_AUTORATE ; 
 int /*<<< orphan*/  TCA_CAKE_BASE_RATE64 ; 
 int /*<<< orphan*/  TCA_CAKE_DIFFSERV_MODE ; 
 int /*<<< orphan*/  TCA_CAKE_FLOW_MODE ; 
 int /*<<< orphan*/  TCA_CAKE_FWMARK ; 
 int /*<<< orphan*/  TCA_CAKE_INGRESS ; 
 int /*<<< orphan*/  TCA_CAKE_MEMORY ; 
 int /*<<< orphan*/  TCA_CAKE_MPU ; 
 int /*<<< orphan*/  TCA_CAKE_NAT ; 
 int /*<<< orphan*/  TCA_CAKE_OVERHEAD ; 
 int /*<<< orphan*/  TCA_CAKE_PAD ; 
 int /*<<< orphan*/  TCA_CAKE_RAW ; 
 int /*<<< orphan*/  TCA_CAKE_RTT ; 
 int /*<<< orphan*/  TCA_CAKE_SPLIT_GSO ; 
 int /*<<< orphan*/  TCA_CAKE_TARGET ; 
 int /*<<< orphan*/  TCA_CAKE_WASH ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cake_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int cake_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	struct cake_sched_data *q = qdisc_priv(sch);
	struct nlattr *opts;

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	if (!opts)
		goto nla_put_failure;

	if (nla_put_u64_64bit(skb, TCA_CAKE_BASE_RATE64, q->rate_bps,
			      TCA_CAKE_PAD))
		goto nla_put_failure;

	if (nla_put_u32(skb, TCA_CAKE_FLOW_MODE,
			q->flow_mode & CAKE_FLOW_MASK))
		goto nla_put_failure;

	if (nla_put_u32(skb, TCA_CAKE_RTT, q->interval))
		goto nla_put_failure;

	if (nla_put_u32(skb, TCA_CAKE_TARGET, q->target))
		goto nla_put_failure;

	if (nla_put_u32(skb, TCA_CAKE_MEMORY, q->buffer_config_limit))
		goto nla_put_failure;

	if (nla_put_u32(skb, TCA_CAKE_AUTORATE,
			!!(q->rate_flags & CAKE_FLAG_AUTORATE_INGRESS)))
		goto nla_put_failure;

	if (nla_put_u32(skb, TCA_CAKE_INGRESS,
			!!(q->rate_flags & CAKE_FLAG_INGRESS)))
		goto nla_put_failure;

	if (nla_put_u32(skb, TCA_CAKE_ACK_FILTER, q->ack_filter))
		goto nla_put_failure;

	if (nla_put_u32(skb, TCA_CAKE_NAT,
			!!(q->flow_mode & CAKE_FLOW_NAT_FLAG)))
		goto nla_put_failure;

	if (nla_put_u32(skb, TCA_CAKE_DIFFSERV_MODE, q->tin_mode))
		goto nla_put_failure;

	if (nla_put_u32(skb, TCA_CAKE_WASH,
			!!(q->rate_flags & CAKE_FLAG_WASH)))
		goto nla_put_failure;

	if (nla_put_u32(skb, TCA_CAKE_OVERHEAD, q->rate_overhead))
		goto nla_put_failure;

	if (!(q->rate_flags & CAKE_FLAG_OVERHEAD))
		if (nla_put_u32(skb, TCA_CAKE_RAW, 0))
			goto nla_put_failure;

	if (nla_put_u32(skb, TCA_CAKE_ATM, q->atm_mode))
		goto nla_put_failure;

	if (nla_put_u32(skb, TCA_CAKE_MPU, q->rate_mpu))
		goto nla_put_failure;

	if (nla_put_u32(skb, TCA_CAKE_SPLIT_GSO,
			!!(q->rate_flags & CAKE_FLAG_SPLIT_GSO)))
		goto nla_put_failure;

	if (nla_put_u32(skb, TCA_CAKE_FWMARK, q->fwmark_mask))
		goto nla_put_failure;

	return nla_nest_end(skb, opts);

nla_put_failure:
	return -1;
}