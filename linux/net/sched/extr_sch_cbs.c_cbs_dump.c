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
struct tc_cbs_qopt {int /*<<< orphan*/  offload; void* idleslope; void* sendslope; int /*<<< orphan*/  locredit; int /*<<< orphan*/  hicredit; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct cbs_sched_data {int /*<<< orphan*/  offload; int /*<<< orphan*/  idleslope; int /*<<< orphan*/  sendslope; int /*<<< orphan*/  locredit; int /*<<< orphan*/  hicredit; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  BYTES_PER_KBIT ; 
 int /*<<< orphan*/  TCA_CBS_PARMS ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 void* div64_s64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_cbs_qopt*) ; 
 struct cbs_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int cbs_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	struct cbs_sched_data *q = qdisc_priv(sch);
	struct tc_cbs_qopt opt = { };
	struct nlattr *nest;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	if (!nest)
		goto nla_put_failure;

	opt.hicredit = q->hicredit;
	opt.locredit = q->locredit;
	opt.sendslope = div64_s64(q->sendslope, BYTES_PER_KBIT);
	opt.idleslope = div64_s64(q->idleslope, BYTES_PER_KBIT);
	opt.offload = q->offload;

	if (nla_put(skb, TCA_CBS_PARMS, sizeof(opt), &opt))
		goto nla_put_failure;

	return nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -1;
}