#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tcmsg {int /*<<< orphan*/  tcm_info; int /*<<< orphan*/  tcm_handle; int /*<<< orphan*/  tcm_parent; } ;
struct tc_htb_opt {scalar_t__ level; int /*<<< orphan*/  prio; int /*<<< orphan*/  quantum; void* cbuffer; int /*<<< orphan*/  ceil; void* buffer; int /*<<< orphan*/  rate; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_12__ {unsigned long long rate_bytes_ps; } ;
struct TYPE_11__ {TYPE_4__* q; } ;
struct TYPE_9__ {int /*<<< orphan*/  classid; } ;
struct htb_class {TYPE_6__ ceil; TYPE_6__ rate; scalar_t__ level; int /*<<< orphan*/  prio; int /*<<< orphan*/  quantum; int /*<<< orphan*/  cbuffer; int /*<<< orphan*/  buffer; TYPE_5__ leaf; TYPE_3__ common; TYPE_2__* parent; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  opt ;
struct TYPE_10__ {int /*<<< orphan*/  handle; } ;
struct TYPE_7__ {int /*<<< orphan*/  classid; } ;
struct TYPE_8__ {TYPE_1__ common; } ;

/* Variables and functions */
 void* PSCHED_NS2TICKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCA_HTB_CEIL64 ; 
 int /*<<< orphan*/  TCA_HTB_PAD ; 
 int /*<<< orphan*/  TCA_HTB_PARMS ; 
 int /*<<< orphan*/  TCA_HTB_RATE64 ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  TC_H_ROOT ; 
 int /*<<< orphan*/  memset (struct tc_htb_opt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_htb_opt*) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psched_ratecfg_getrate (int /*<<< orphan*/ *,TYPE_6__*) ; 

__attribute__((used)) static int htb_dump_class(struct Qdisc *sch, unsigned long arg,
			  struct sk_buff *skb, struct tcmsg *tcm)
{
	struct htb_class *cl = (struct htb_class *)arg;
	struct nlattr *nest;
	struct tc_htb_opt opt;

	/* Its safe to not acquire qdisc lock. As we hold RTNL,
	 * no change can happen on the class parameters.
	 */
	tcm->tcm_parent = cl->parent ? cl->parent->common.classid : TC_H_ROOT;
	tcm->tcm_handle = cl->common.classid;
	if (!cl->level && cl->leaf.q)
		tcm->tcm_info = cl->leaf.q->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	if (nest == NULL)
		goto nla_put_failure;

	memset(&opt, 0, sizeof(opt));

	psched_ratecfg_getrate(&opt.rate, &cl->rate);
	opt.buffer = PSCHED_NS2TICKS(cl->buffer);
	psched_ratecfg_getrate(&opt.ceil, &cl->ceil);
	opt.cbuffer = PSCHED_NS2TICKS(cl->cbuffer);
	opt.quantum = cl->quantum;
	opt.prio = cl->prio;
	opt.level = cl->level;
	if (nla_put(skb, TCA_HTB_PARMS, sizeof(opt), &opt))
		goto nla_put_failure;
	if ((cl->rate.rate_bytes_ps >= (1ULL << 32)) &&
	    nla_put_u64_64bit(skb, TCA_HTB_RATE64, cl->rate.rate_bytes_ps,
			      TCA_HTB_PAD))
		goto nla_put_failure;
	if ((cl->ceil.rate_bytes_ps >= (1ULL << 32)) &&
	    nla_put_u64_64bit(skb, TCA_HTB_CEIL64, cl->ceil.rate_bytes_ps,
			      TCA_HTB_PAD))
		goto nla_put_failure;

	return nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -1;
}