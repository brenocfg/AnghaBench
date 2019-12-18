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
struct sk_buff {int dummy; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct Qdisc {int flags; int (* enqueue ) (struct sk_buff*,struct Qdisc*,struct sk_buff**) ;int /*<<< orphan*/  busylock; int /*<<< orphan*/  state; scalar_t__ empty; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int NET_XMIT_DROP ; 
 int NET_XMIT_MASK ; 
 int NET_XMIT_SUCCESS ; 
 int TCQ_F_CAN_BYPASS ; 
 int TCQ_F_NOLOCK ; 
 int /*<<< orphan*/  __QDISC_STATE_DEACTIVATED ; 
 int /*<<< orphan*/  __qdisc_drop (struct sk_buff*,struct sk_buff**) ; 
 int /*<<< orphan*/  __qdisc_run (struct Qdisc*) ; 
 int /*<<< orphan*/  kfree_skb_list (struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_bstats_cpu_update (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_bstats_update (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_calculate_pkt_len (struct sk_buff*,struct Qdisc*) ; 
 int qdisc_is_running (struct Qdisc*) ; 
 int /*<<< orphan*/ * qdisc_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qlen (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_run (struct Qdisc*) ; 
 scalar_t__ qdisc_run_begin (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_run_end (struct Qdisc*) ; 
 scalar_t__ sch_direct_xmit (struct sk_buff*,struct Qdisc*,struct net_device*,struct netdev_queue*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 int stub2 (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int __dev_xmit_skb(struct sk_buff *skb, struct Qdisc *q,
				 struct net_device *dev,
				 struct netdev_queue *txq)
{
	spinlock_t *root_lock = qdisc_lock(q);
	struct sk_buff *to_free = NULL;
	bool contended;
	int rc;

	qdisc_calculate_pkt_len(skb, q);

	if (q->flags & TCQ_F_NOLOCK) {
		if ((q->flags & TCQ_F_CAN_BYPASS) && q->empty &&
		    qdisc_run_begin(q)) {
			if (unlikely(test_bit(__QDISC_STATE_DEACTIVATED,
					      &q->state))) {
				__qdisc_drop(skb, &to_free);
				rc = NET_XMIT_DROP;
				goto end_run;
			}
			qdisc_bstats_cpu_update(q, skb);

			rc = NET_XMIT_SUCCESS;
			if (sch_direct_xmit(skb, q, dev, txq, NULL, true))
				__qdisc_run(q);

end_run:
			qdisc_run_end(q);
		} else {
			rc = q->enqueue(skb, q, &to_free) & NET_XMIT_MASK;
			qdisc_run(q);
		}

		if (unlikely(to_free))
			kfree_skb_list(to_free);
		return rc;
	}

	/*
	 * Heuristic to force contended enqueues to serialize on a
	 * separate lock before trying to get qdisc main lock.
	 * This permits qdisc->running owner to get the lock more
	 * often and dequeue packets faster.
	 */
	contended = qdisc_is_running(q);
	if (unlikely(contended))
		spin_lock(&q->busylock);

	spin_lock(root_lock);
	if (unlikely(test_bit(__QDISC_STATE_DEACTIVATED, &q->state))) {
		__qdisc_drop(skb, &to_free);
		rc = NET_XMIT_DROP;
	} else if ((q->flags & TCQ_F_CAN_BYPASS) && !qdisc_qlen(q) &&
		   qdisc_run_begin(q)) {
		/*
		 * This is a work-conserving queue; there are no old skbs
		 * waiting to be sent out; and the qdisc is not running -
		 * xmit the skb directly.
		 */

		qdisc_bstats_update(q, skb);

		if (sch_direct_xmit(skb, q, dev, txq, root_lock, true)) {
			if (unlikely(contended)) {
				spin_unlock(&q->busylock);
				contended = false;
			}
			__qdisc_run(q);
		}

		qdisc_run_end(q);
		rc = NET_XMIT_SUCCESS;
	} else {
		rc = q->enqueue(skb, q, &to_free) & NET_XMIT_MASK;
		if (qdisc_run_begin(q)) {
			if (unlikely(contended)) {
				spin_unlock(&q->busylock);
				contended = false;
			}
			__qdisc_run(q);
			qdisc_run_end(q);
		}
	}
	spin_unlock(root_lock);
	if (unlikely(to_free))
		kfree_skb_list(to_free);
	if (unlikely(contended))
		spin_unlock(&q->busylock);
	return rc;
}