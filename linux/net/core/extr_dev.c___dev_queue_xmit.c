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
struct sk_buff {scalar_t__ tc_at_ingress; int /*<<< orphan*/  sk; struct net_device* dev; } ;
struct netdev_queue {int xmit_lock_owner; int /*<<< orphan*/  qdisc; } ;
struct net_device {int priv_flags; int flags; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  name; } ;
struct Qdisc {scalar_t__ enqueue; } ;
struct TYPE_2__ {int tx_flags; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HARD_TX_LOCK (struct net_device*,struct netdev_queue*,int) ; 
 int /*<<< orphan*/  HARD_TX_UNLOCK (struct net_device*,struct netdev_queue*) ; 
 int IFF_UP ; 
 int IFF_XMIT_DST_RELEASE ; 
 int /*<<< orphan*/  SCM_TSTAMP_SCHED ; 
 int SKBTX_SCHED_TSTAMP ; 
 int __dev_xmit_skb (struct sk_buff*,struct Qdisc*,struct net_device*,struct netdev_queue*) ; 
 int /*<<< orphan*/  __skb_tstamp_tx (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 struct sk_buff* dev_hard_start_xmit (struct sk_buff*,struct net_device*,struct netdev_queue*,int*) ; 
 scalar_t__ dev_xmit_complete (int) ; 
 scalar_t__ dev_xmit_recursion () ; 
 int /*<<< orphan*/  dev_xmit_recursion_dec () ; 
 int /*<<< orphan*/  dev_xmit_recursion_inc () ; 
 int /*<<< orphan*/  egress_needed_key ; 
 int /*<<< orphan*/  kfree_skb_list (struct sk_buff*) ; 
 int /*<<< orphan*/  net_crit_ratelimited (char*,int /*<<< orphan*/ ) ; 
 struct netdev_queue* netdev_core_pick_tx (struct net_device*,struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  netif_xmit_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  qdisc_pkt_len_init (struct sk_buff*) ; 
 struct Qdisc* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 struct sk_buff* sch_handle_egress (struct sk_buff*,int*,struct net_device*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_force (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_update_prio (struct sk_buff*) ; 
 int smp_processor_id () ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_net_dev_queue (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 struct sk_buff* validate_xmit_skb (struct sk_buff*,struct net_device*,int*) ; 

__attribute__((used)) static int __dev_queue_xmit(struct sk_buff *skb, struct net_device *sb_dev)
{
	struct net_device *dev = skb->dev;
	struct netdev_queue *txq;
	struct Qdisc *q;
	int rc = -ENOMEM;
	bool again = false;

	skb_reset_mac_header(skb);

	if (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_SCHED_TSTAMP))
		__skb_tstamp_tx(skb, NULL, skb->sk, SCM_TSTAMP_SCHED);

	/* Disable soft irqs for various locks below. Also
	 * stops preemption for RCU.
	 */
	rcu_read_lock_bh();

	skb_update_prio(skb);

	qdisc_pkt_len_init(skb);
#ifdef CONFIG_NET_CLS_ACT
	skb->tc_at_ingress = 0;
# ifdef CONFIG_NET_EGRESS
	if (static_branch_unlikely(&egress_needed_key)) {
		skb = sch_handle_egress(skb, &rc, dev);
		if (!skb)
			goto out;
	}
# endif
#endif
	/* If device/qdisc don't need skb->dst, release it right now while
	 * its hot in this cpu cache.
	 */
	if (dev->priv_flags & IFF_XMIT_DST_RELEASE)
		skb_dst_drop(skb);
	else
		skb_dst_force(skb);

	txq = netdev_core_pick_tx(dev, skb, sb_dev);
	q = rcu_dereference_bh(txq->qdisc);

	trace_net_dev_queue(skb);
	if (q->enqueue) {
		rc = __dev_xmit_skb(skb, q, dev, txq);
		goto out;
	}

	/* The device has no queue. Common case for software devices:
	 * loopback, all the sorts of tunnels...

	 * Really, it is unlikely that netif_tx_lock protection is necessary
	 * here.  (f.e. loopback and IP tunnels are clean ignoring statistics
	 * counters.)
	 * However, it is possible, that they rely on protection
	 * made by us here.

	 * Check this and shot the lock. It is not prone from deadlocks.
	 *Either shot noqueue qdisc, it is even simpler 8)
	 */
	if (dev->flags & IFF_UP) {
		int cpu = smp_processor_id(); /* ok because BHs are off */

		if (txq->xmit_lock_owner != cpu) {
			if (dev_xmit_recursion())
				goto recursion_alert;

			skb = validate_xmit_skb(skb, dev, &again);
			if (!skb)
				goto out;

			HARD_TX_LOCK(dev, txq, cpu);

			if (!netif_xmit_stopped(txq)) {
				dev_xmit_recursion_inc();
				skb = dev_hard_start_xmit(skb, dev, txq, &rc);
				dev_xmit_recursion_dec();
				if (dev_xmit_complete(rc)) {
					HARD_TX_UNLOCK(dev, txq);
					goto out;
				}
			}
			HARD_TX_UNLOCK(dev, txq);
			net_crit_ratelimited("Virtual device %s asks to queue packet!\n",
					     dev->name);
		} else {
			/* Recursion is detected! It is possible,
			 * unfortunately
			 */
recursion_alert:
			net_crit_ratelimited("Dead loop on virtual device %s, fix it urgently!\n",
					     dev->name);
		}
	}

	rc = -ENETDOWN;
	rcu_read_unlock_bh();

	atomic_long_inc(&dev->tx_dropped);
	kfree_skb_list(skb);
	return rc;
out:
	rcu_read_unlock_bh();
	return rc;
}