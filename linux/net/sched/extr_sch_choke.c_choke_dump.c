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
struct tc_red_qopt {int qth_min; int qth_max; int Wlog; int /*<<< orphan*/  Scell_log; int /*<<< orphan*/  Plog; int /*<<< orphan*/  flags; int /*<<< orphan*/  limit; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int qth_min; int Wlog; int qth_max; int /*<<< orphan*/  max_P; int /*<<< orphan*/  Scell_log; int /*<<< orphan*/  Plog; } ;
struct choke_sched_data {TYPE_1__ parms; int /*<<< orphan*/  flags; int /*<<< orphan*/  limit; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  TCA_CHOKE_MAX_P ; 
 int /*<<< orphan*/  TCA_CHOKE_PARMS ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_red_qopt*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct choke_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int choke_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	struct choke_sched_data *q = qdisc_priv(sch);
	struct nlattr *opts = NULL;
	struct tc_red_qopt opt = {
		.limit		= q->limit,
		.flags		= q->flags,
		.qth_min	= q->parms.qth_min >> q->parms.Wlog,
		.qth_max	= q->parms.qth_max >> q->parms.Wlog,
		.Wlog		= q->parms.Wlog,
		.Plog		= q->parms.Plog,
		.Scell_log	= q->parms.Scell_log,
	};

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	if (opts == NULL)
		goto nla_put_failure;

	if (nla_put(skb, TCA_CHOKE_PARMS, sizeof(opt), &opt) ||
	    nla_put_u32(skb, TCA_CHOKE_MAX_P, q->parms.max_P))
		goto nla_put_failure;
	return nla_nest_end(skb, opts);

nla_put_failure:
	nla_nest_cancel(skb, opts);
	return -EMSGSIZE;
}