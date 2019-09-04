#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {struct sk_buff* next; } ;
struct TYPE_4__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_3__ {int /*<<< orphan*/  requeues; } ;
struct Qdisc {TYPE_2__ q; TYPE_1__ qstats; int /*<<< orphan*/  gso_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  __netif_schedule (struct Qdisc*) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_inc (struct Qdisc*,struct sk_buff*) ; 

__attribute__((used)) static inline int __dev_requeue_skb(struct sk_buff *skb, struct Qdisc *q)
{
	while (skb) {
		struct sk_buff *next = skb->next;

		__skb_queue_tail(&q->gso_skb, skb);
		q->qstats.requeues++;
		qdisc_qstats_backlog_inc(q, skb);
		q->q.qlen++;	/* it's still part of the queue */

		skb = next;
	}
	__netif_schedule(q);

	return 0;
}