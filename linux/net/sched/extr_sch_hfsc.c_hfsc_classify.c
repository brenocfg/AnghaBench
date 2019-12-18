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
struct tcf_result {int classid; scalar_t__ class; } ;
struct tcf_proto {int dummy; } ;
struct sk_buff {int priority; } ;
struct hfsc_class {scalar_t__ level; int /*<<< orphan*/  filter_list; } ;
struct hfsc_sched {int /*<<< orphan*/  defcls; struct hfsc_class root; } ;
struct Qdisc {int handle; } ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
#define  TC_ACT_QUEUED 131 
#define  TC_ACT_SHOT 130 
#define  TC_ACT_STOLEN 129 
#define  TC_ACT_TRAP 128 
 scalar_t__ TC_H_MAJ (int) ; 
 int TC_H_MAKE (scalar_t__,int /*<<< orphan*/ ) ; 
 int __NET_XMIT_BYPASS ; 
 int __NET_XMIT_STOLEN ; 
 struct hfsc_class* hfsc_find_class (int,struct Qdisc*) ; 
 struct hfsc_sched* qdisc_priv (struct Qdisc*) ; 
 struct tcf_proto* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int tcf_classify (struct sk_buff*,struct tcf_proto*,struct tcf_result*,int) ; 

__attribute__((used)) static struct hfsc_class *
hfsc_classify(struct sk_buff *skb, struct Qdisc *sch, int *qerr)
{
	struct hfsc_sched *q = qdisc_priv(sch);
	struct hfsc_class *head, *cl;
	struct tcf_result res;
	struct tcf_proto *tcf;
	int result;

	if (TC_H_MAJ(skb->priority ^ sch->handle) == 0 &&
	    (cl = hfsc_find_class(skb->priority, sch)) != NULL)
		if (cl->level == 0)
			return cl;

	*qerr = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	head = &q->root;
	tcf = rcu_dereference_bh(q->root.filter_list);
	while (tcf && (result = tcf_classify(skb, tcf, &res, false)) >= 0) {
#ifdef CONFIG_NET_CLS_ACT
		switch (result) {
		case TC_ACT_QUEUED:
		case TC_ACT_STOLEN:
		case TC_ACT_TRAP:
			*qerr = NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;
			/* fall through */
		case TC_ACT_SHOT:
			return NULL;
		}
#endif
		cl = (struct hfsc_class *)res.class;
		if (!cl) {
			cl = hfsc_find_class(res.classid, sch);
			if (!cl)
				break; /* filter selected invalid classid */
			if (cl->level >= head->level)
				break; /* filter may only point downwards */
		}

		if (cl->level == 0)
			return cl; /* hit leaf class */

		/* apply inner filter chain */
		tcf = rcu_dereference_bh(cl->filter_list);
		head = cl;
	}

	/* classification failed, try default class */
	cl = hfsc_find_class(TC_H_MAKE(TC_H_MAJ(sch->handle), q->defcls), sch);
	if (cl == NULL || cl->level > 0)
		return NULL;

	return cl;
}