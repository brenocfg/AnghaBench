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
struct netdev_queue {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_1__ q; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  HARD_TX_LOCK (struct net_device*,struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HARD_TX_UNLOCK (struct net_device*,struct netdev_queue*) ; 
 int NETDEV_TX_BUSY ; 
 struct sk_buff* dev_hard_start_xmit (struct sk_buff*,struct net_device*,struct netdev_queue*,int*) ; 
 int /*<<< orphan*/  dev_requeue_skb (struct sk_buff*,struct Qdisc*) ; 
 int /*<<< orphan*/  dev_xmit_complete (int) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_xmit_frozen_or_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct sk_buff* validate_xmit_skb_list (struct sk_buff*,struct net_device*,int*) ; 

bool sch_direct_xmit(struct sk_buff *skb, struct Qdisc *q,
		     struct net_device *dev, struct netdev_queue *txq,
		     spinlock_t *root_lock, bool validate)
{
	int ret = NETDEV_TX_BUSY;
	bool again = false;

	/* And release qdisc */
	if (root_lock)
		spin_unlock(root_lock);

	/* Note that we validate skb (GSO, checksum, ...) outside of locks */
	if (validate)
		skb = validate_xmit_skb_list(skb, dev, &again);

#ifdef CONFIG_XFRM_OFFLOAD
	if (unlikely(again)) {
		if (root_lock)
			spin_lock(root_lock);

		dev_requeue_skb(skb, q);
		return false;
	}
#endif

	if (likely(skb)) {
		HARD_TX_LOCK(dev, txq, smp_processor_id());
		if (!netif_xmit_frozen_or_stopped(txq))
			skb = dev_hard_start_xmit(skb, dev, txq, &ret);

		HARD_TX_UNLOCK(dev, txq);
	} else {
		if (root_lock)
			spin_lock(root_lock);
		return true;
	}

	if (root_lock)
		spin_lock(root_lock);

	if (!dev_xmit_complete(ret)) {
		/* Driver returned NETDEV_TX_BUSY - requeue skb */
		if (unlikely(ret != NETDEV_TX_BUSY))
			net_warn_ratelimited("BUG %s code %d qlen %d\n",
					     dev->name, ret, q->q.qlen);

		dev_requeue_skb(skb, q);
		return false;
	}

	return true;
}