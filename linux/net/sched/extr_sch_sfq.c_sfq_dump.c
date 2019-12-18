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
struct TYPE_2__ {int perturb_period; int /*<<< orphan*/  flows; int /*<<< orphan*/  divisor; int /*<<< orphan*/  limit; int /*<<< orphan*/  quantum; } ;
struct tc_sfq_qopt_v1 {int qth_min; int qth_max; int Wlog; int /*<<< orphan*/  flags; int /*<<< orphan*/  stats; int /*<<< orphan*/  max_P; int /*<<< orphan*/  Scell_log; int /*<<< orphan*/  Plog; int /*<<< orphan*/  headdrop; int /*<<< orphan*/  depth; TYPE_1__ v0; } ;
struct sk_buff {int len; } ;
struct sfq_sched_data {int perturb_period; int /*<<< orphan*/  flags; int /*<<< orphan*/  stats; int /*<<< orphan*/  headdrop; int /*<<< orphan*/  maxdepth; int /*<<< orphan*/  maxflows; int /*<<< orphan*/  divisor; int /*<<< orphan*/  limit; int /*<<< orphan*/  quantum; struct red_parms* red_parms; } ;
struct red_parms {int qth_min; int Wlog; int qth_max; int /*<<< orphan*/  max_P; int /*<<< orphan*/  Scell_log; int /*<<< orphan*/  Plog; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct tc_sfq_qopt_v1*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_sfq_qopt_v1*) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 struct sfq_sched_data* qdisc_priv (struct Qdisc*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static int sfq_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	struct sfq_sched_data *q = qdisc_priv(sch);
	unsigned char *b = skb_tail_pointer(skb);
	struct tc_sfq_qopt_v1 opt;
	struct red_parms *p = q->red_parms;

	memset(&opt, 0, sizeof(opt));
	opt.v0.quantum	= q->quantum;
	opt.v0.perturb_period = q->perturb_period / HZ;
	opt.v0.limit	= q->limit;
	opt.v0.divisor	= q->divisor;
	opt.v0.flows	= q->maxflows;
	opt.depth	= q->maxdepth;
	opt.headdrop	= q->headdrop;

	if (p) {
		opt.qth_min	= p->qth_min >> p->Wlog;
		opt.qth_max	= p->qth_max >> p->Wlog;
		opt.Wlog	= p->Wlog;
		opt.Plog	= p->Plog;
		opt.Scell_log	= p->Scell_log;
		opt.max_P	= p->max_P;
	}
	memcpy(&opt.stats, &q->stats, sizeof(opt.stats));
	opt.flags	= q->flags;

	if (nla_put(skb, TCA_OPTIONS, sizeof(opt), &opt))
		goto nla_put_failure;

	return skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	return -1;
}