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
struct tcf_result {int /*<<< orphan*/  classid; } ;
struct tcf_proto {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  priority; } ;
struct sfq_sched_data {scalar_t__ divisor; int /*<<< orphan*/  filter_list; } ;
struct Qdisc {scalar_t__ handle; } ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
#define  TC_ACT_QUEUED 131 
#define  TC_ACT_SHOT 130 
#define  TC_ACT_STOLEN 129 
#define  TC_ACT_TRAP 128 
 scalar_t__ TC_H_MAJ (int /*<<< orphan*/ ) ; 
 unsigned int TC_H_MIN (int /*<<< orphan*/ ) ; 
 int __NET_XMIT_BYPASS ; 
 int __NET_XMIT_STOLEN ; 
 struct sfq_sched_data* qdisc_priv (struct Qdisc*) ; 
 struct tcf_proto* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 unsigned int sfq_hash (struct sfq_sched_data*,struct sk_buff*) ; 
 int tcf_classify (struct sk_buff*,struct tcf_proto*,struct tcf_result*,int) ; 

__attribute__((used)) static unsigned int sfq_classify(struct sk_buff *skb, struct Qdisc *sch,
				 int *qerr)
{
	struct sfq_sched_data *q = qdisc_priv(sch);
	struct tcf_result res;
	struct tcf_proto *fl;
	int result;

	if (TC_H_MAJ(skb->priority) == sch->handle &&
	    TC_H_MIN(skb->priority) > 0 &&
	    TC_H_MIN(skb->priority) <= q->divisor)
		return TC_H_MIN(skb->priority);

	fl = rcu_dereference_bh(q->filter_list);
	if (!fl)
		return sfq_hash(q, skb) + 1;

	*qerr = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	result = tcf_classify(skb, fl, &res, false);
	if (result >= 0) {
#ifdef CONFIG_NET_CLS_ACT
		switch (result) {
		case TC_ACT_STOLEN:
		case TC_ACT_QUEUED:
		case TC_ACT_TRAP:
			*qerr = NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;
			/* fall through */
		case TC_ACT_SHOT:
			return 0;
		}
#endif
		if (TC_H_MIN(res.classid) <= q->divisor)
			return TC_H_MIN(res.classid);
	}
	return 0;
}