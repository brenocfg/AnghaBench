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
struct Qdisc {int flags; struct sk_buff* (* dequeue ) (struct Qdisc*) ;TYPE_1__ q; int /*<<< orphan*/  gso_skb; struct netdev_queue* dev_queue; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 struct sk_buff* SKB_XOFF_MAGIC ; 
 int TCQ_F_NOLOCK ; 
 int TCQ_F_ONETXQUEUE ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ netif_xmit_frozen_or_stopped (struct netdev_queue const*) ; 
 struct sk_buff* qdisc_dequeue_skb_bad_txq (struct Qdisc*) ; 
 scalar_t__ qdisc_is_percpu_stats (struct Qdisc*) ; 
 int /*<<< orphan*/ * qdisc_lock (struct Qdisc*) ; 
 scalar_t__ qdisc_may_bulk (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_dec (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_qstats_cpu_backlog_dec (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_qstats_cpu_qlen_dec (struct Qdisc*) ; 
 struct netdev_queue* skb_get_tx_queue (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct sk_buff* stub1 (struct Qdisc*) ; 
 int /*<<< orphan*/  trace_qdisc_dequeue (struct Qdisc*,struct netdev_queue const*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  try_bulk_dequeue_skb (struct Qdisc*,struct sk_buff*,struct netdev_queue const*,int*) ; 
 int /*<<< orphan*/  try_bulk_dequeue_skb_slow (struct Qdisc*,struct sk_buff*,int*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ xfrm_offload (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *dequeue_skb(struct Qdisc *q, bool *validate,
				   int *packets)
{
	const struct netdev_queue *txq = q->dev_queue;
	struct sk_buff *skb = NULL;

	*packets = 1;
	if (unlikely(!skb_queue_empty(&q->gso_skb))) {
		spinlock_t *lock = NULL;

		if (q->flags & TCQ_F_NOLOCK) {
			lock = qdisc_lock(q);
			spin_lock(lock);
		}

		skb = skb_peek(&q->gso_skb);

		/* skb may be null if another cpu pulls gso_skb off in between
		 * empty check and lock.
		 */
		if (!skb) {
			if (lock)
				spin_unlock(lock);
			goto validate;
		}

		/* skb in gso_skb were already validated */
		*validate = false;
		if (xfrm_offload(skb))
			*validate = true;
		/* check the reason of requeuing without tx lock first */
		txq = skb_get_tx_queue(txq->dev, skb);
		if (!netif_xmit_frozen_or_stopped(txq)) {
			skb = __skb_dequeue(&q->gso_skb);
			if (qdisc_is_percpu_stats(q)) {
				qdisc_qstats_cpu_backlog_dec(q, skb);
				qdisc_qstats_cpu_qlen_dec(q);
			} else {
				qdisc_qstats_backlog_dec(q, skb);
				q->q.qlen--;
			}
		} else {
			skb = NULL;
		}
		if (lock)
			spin_unlock(lock);
		goto trace;
	}
validate:
	*validate = true;

	if ((q->flags & TCQ_F_ONETXQUEUE) &&
	    netif_xmit_frozen_or_stopped(txq))
		return skb;

	skb = qdisc_dequeue_skb_bad_txq(q);
	if (unlikely(skb)) {
		if (skb == SKB_XOFF_MAGIC)
			return NULL;
		goto bulk;
	}
	skb = q->dequeue(q);
	if (skb) {
bulk:
		if (qdisc_may_bulk(q))
			try_bulk_dequeue_skb(q, skb, txq, packets);
		else
			try_bulk_dequeue_skb_slow(q, skb, packets);
	}
trace:
	trace_qdisc_dequeue(q, txq, *packets, skb);
	return skb;
}