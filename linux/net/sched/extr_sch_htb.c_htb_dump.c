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
struct tc_htb_glob {scalar_t__ debug; int /*<<< orphan*/  defcls; int /*<<< orphan*/  rate2quantum; int /*<<< orphan*/  version; int /*<<< orphan*/  direct_pkts; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct htb_sched {int /*<<< orphan*/  direct_qlen; int /*<<< orphan*/  defcls; int /*<<< orphan*/  rate2quantum; int /*<<< orphan*/  direct_pkts; int /*<<< orphan*/  overlimits; } ;
struct TYPE_2__ {int /*<<< orphan*/  overlimits; } ;
struct Qdisc {TYPE_1__ qstats; } ;
typedef  int /*<<< orphan*/  gopt ;

/* Variables and functions */
 int /*<<< orphan*/  HTB_VER ; 
 int /*<<< orphan*/  TCA_HTB_DIRECT_QLEN ; 
 int /*<<< orphan*/  TCA_HTB_INIT ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_htb_glob*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct htb_sched* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int htb_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	struct htb_sched *q = qdisc_priv(sch);
	struct nlattr *nest;
	struct tc_htb_glob gopt;

	sch->qstats.overlimits = q->overlimits;
	/* Its safe to not acquire qdisc lock. As we hold RTNL,
	 * no change can happen on the qdisc parameters.
	 */

	gopt.direct_pkts = q->direct_pkts;
	gopt.version = HTB_VER;
	gopt.rate2quantum = q->rate2quantum;
	gopt.defcls = q->defcls;
	gopt.debug = 0;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	if (nest == NULL)
		goto nla_put_failure;
	if (nla_put(skb, TCA_HTB_INIT, sizeof(gopt), &gopt) ||
	    nla_put_u32(skb, TCA_HTB_DIRECT_QLEN, q->direct_qlen))
		goto nla_put_failure;

	return nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -1;
}