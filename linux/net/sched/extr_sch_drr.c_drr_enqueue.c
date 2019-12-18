#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct drr_sched {int /*<<< orphan*/  active; } ;
struct TYPE_7__ {int /*<<< orphan*/  drops; } ;
struct drr_class {int /*<<< orphan*/  quantum; int /*<<< orphan*/  deficit; int /*<<< orphan*/  alist; TYPE_2__ qstats; TYPE_5__* qdisc; } ;
struct TYPE_9__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_8__ {unsigned int backlog; } ;
struct Qdisc {TYPE_4__ q; TYPE_3__ qstats; } ;
struct TYPE_6__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_10__ {TYPE_1__ q; } ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
 int __NET_XMIT_BYPASS ; 
 int /*<<< orphan*/  __qdisc_drop (struct sk_buff*,struct sk_buff**) ; 
 struct drr_class* drr_classify (struct sk_buff*,struct Qdisc*,int*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ net_xmit_drop_count (int) ; 
 int qdisc_enqueue (struct sk_buff*,TYPE_5__*,struct sk_buff**) ; 
 unsigned int qdisc_pkt_len (struct sk_buff*) ; 
 struct drr_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_drop (struct Qdisc*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int drr_enqueue(struct sk_buff *skb, struct Qdisc *sch,
		       struct sk_buff **to_free)
{
	unsigned int len = qdisc_pkt_len(skb);
	struct drr_sched *q = qdisc_priv(sch);
	struct drr_class *cl;
	int err = 0;
	bool first;

	cl = drr_classify(skb, sch, &err);
	if (cl == NULL) {
		if (err & __NET_XMIT_BYPASS)
			qdisc_qstats_drop(sch);
		__qdisc_drop(skb, to_free);
		return err;
	}

	first = !cl->qdisc->q.qlen;
	err = qdisc_enqueue(skb, cl->qdisc, to_free);
	if (unlikely(err != NET_XMIT_SUCCESS)) {
		if (net_xmit_drop_count(err)) {
			cl->qstats.drops++;
			qdisc_qstats_drop(sch);
		}
		return err;
	}

	if (first) {
		list_add_tail(&cl->alist, &q->active);
		cl->deficit = cl->quantum;
	}

	sch->qstats.backlog += len;
	sch->q.qlen++;
	return err;
}