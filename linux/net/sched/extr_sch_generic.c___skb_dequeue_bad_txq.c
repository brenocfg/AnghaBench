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
struct sk_buff {int dummy; } ;
struct netdev_queue {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {int flags; TYPE_1__ q; int /*<<< orphan*/  skb_bad_txq; struct netdev_queue* dev_queue; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 struct sk_buff* SKB_XOFF_MAGIC ; 
 int TCQ_F_NOLOCK ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_xmit_frozen_or_stopped (struct netdev_queue const*) ; 
 scalar_t__ qdisc_is_percpu_stats (struct Qdisc*) ; 
 int /*<<< orphan*/ * qdisc_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_dec (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_qstats_cpu_backlog_dec (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_qstats_cpu_qlen_dec (struct Qdisc*) ; 
 struct netdev_queue* skb_get_tx_queue (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct sk_buff *__skb_dequeue_bad_txq(struct Qdisc *q)
{
	const struct netdev_queue *txq = q->dev_queue;
	spinlock_t *lock = NULL;
	struct sk_buff *skb;

	if (q->flags & TCQ_F_NOLOCK) {
		lock = qdisc_lock(q);
		spin_lock(lock);
	}

	skb = skb_peek(&q->skb_bad_txq);
	if (skb) {
		/* check the reason of requeuing without tx lock first */
		txq = skb_get_tx_queue(txq->dev, skb);
		if (!netif_xmit_frozen_or_stopped(txq)) {
			skb = __skb_dequeue(&q->skb_bad_txq);
			if (qdisc_is_percpu_stats(q)) {
				qdisc_qstats_cpu_backlog_dec(q, skb);
				qdisc_qstats_cpu_qlen_dec(q);
			} else {
				qdisc_qstats_backlog_dec(q, skb);
				q->q.qlen--;
			}
		} else {
			skb = SKB_XOFF_MAGIC;
		}
	}

	if (lock)
		spin_unlock(lock);

	return skb;
}