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
struct sk_buff {int dummy; } ;
struct netpoll_info {int /*<<< orphan*/  tx_work; int /*<<< orphan*/  txq; } ;
struct netpoll {TYPE_2__* dev; } ;
struct netdev_queue {int dummy; } ;
struct net_device {TYPE_1__* netdev_ops; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  npinfo; } ;
struct TYPE_3__ {int /*<<< orphan*/  ndo_start_xmit; } ;

/* Variables and functions */
 scalar_t__ HARD_TX_TRYLOCK (struct net_device*,struct netdev_queue*) ; 
 int /*<<< orphan*/  HARD_TX_UNLOCK (struct net_device*,struct netdev_queue*) ; 
 int NETDEV_TX_BUSY ; 
 unsigned long USEC_PER_POLL ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 scalar_t__ dev_xmit_complete (int) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 unsigned long jiffies_to_usecs (int) ; 
 int /*<<< orphan*/  lockdep_assert_irqs_disabled () ; 
 struct netdev_queue* netdev_core_pick_tx (struct net_device*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_xmit_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netpoll_owner_active (struct net_device*) ; 
 int /*<<< orphan*/  netpoll_poll_dev (TYPE_2__*) ; 
 int netpoll_start_xmit (struct sk_buff*,struct net_device*,struct netdev_queue*) ; 
 struct netpoll_info* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  udelay (unsigned long) ; 

void netpoll_send_skb_on_dev(struct netpoll *np, struct sk_buff *skb,
			     struct net_device *dev)
{
	int status = NETDEV_TX_BUSY;
	unsigned long tries;
	/* It is up to the caller to keep npinfo alive. */
	struct netpoll_info *npinfo;

	lockdep_assert_irqs_disabled();

	npinfo = rcu_dereference_bh(np->dev->npinfo);
	if (!npinfo || !netif_running(dev) || !netif_device_present(dev)) {
		dev_kfree_skb_irq(skb);
		return;
	}

	/* don't get messages out of order, and no recursion */
	if (skb_queue_len(&npinfo->txq) == 0 && !netpoll_owner_active(dev)) {
		struct netdev_queue *txq;

		txq = netdev_core_pick_tx(dev, skb, NULL);

		/* try until next clock tick */
		for (tries = jiffies_to_usecs(1)/USEC_PER_POLL;
		     tries > 0; --tries) {
			if (HARD_TX_TRYLOCK(dev, txq)) {
				if (!netif_xmit_stopped(txq))
					status = netpoll_start_xmit(skb, dev, txq);

				HARD_TX_UNLOCK(dev, txq);

				if (dev_xmit_complete(status))
					break;

			}

			/* tickle device maybe there is some cleanup */
			netpoll_poll_dev(np->dev);

			udelay(USEC_PER_POLL);
		}

		WARN_ONCE(!irqs_disabled(),
			"netpoll_send_skb_on_dev(): %s enabled interrupts in poll (%pS)\n",
			dev->name, dev->netdev_ops->ndo_start_xmit);

	}

	if (!dev_xmit_complete(status)) {
		skb_queue_tail(&npinfo->txq, skb);
		schedule_delayed_work(&npinfo->tx_work,0);
	}
}