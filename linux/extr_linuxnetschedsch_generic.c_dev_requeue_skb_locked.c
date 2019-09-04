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
struct sk_buff {struct sk_buff* next; } ;
struct Qdisc {int /*<<< orphan*/  gso_skb; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  __netif_schedule (struct Qdisc*) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/ * qdisc_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_atomic_qlen_inc (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_cpu_backlog_inc (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_qstats_cpu_requeues_inc (struct Qdisc*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int dev_requeue_skb_locked(struct sk_buff *skb, struct Qdisc *q)
{
	spinlock_t *lock = qdisc_lock(q);

	spin_lock(lock);
	while (skb) {
		struct sk_buff *next = skb->next;

		__skb_queue_tail(&q->gso_skb, skb);

		qdisc_qstats_cpu_requeues_inc(q);
		qdisc_qstats_cpu_backlog_inc(q, skb);
		qdisc_qstats_atomic_qlen_inc(q);

		skb = next;
	}
	spin_unlock(lock);

	__netif_schedule(q);

	return 0;
}