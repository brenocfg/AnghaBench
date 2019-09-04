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
struct net_device {int num_tx_queues; } ;
struct ifb_q_private {int txqnum; int /*<<< orphan*/  ifb_tasklet; int /*<<< orphan*/  tsync; int /*<<< orphan*/  rsync; int /*<<< orphan*/  tq; int /*<<< orphan*/  rq; struct net_device* dev; } ;
struct ifb_dev_private {struct ifb_q_private* tx_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifb_ri_tasklet ; 
 struct ifb_q_private* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_get_tx_queue (struct net_device*,int) ; 
 struct ifb_dev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  u64_stats_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ifb_dev_init(struct net_device *dev)
{
	struct ifb_dev_private *dp = netdev_priv(dev);
	struct ifb_q_private *txp;
	int i;

	txp = kcalloc(dev->num_tx_queues, sizeof(*txp), GFP_KERNEL);
	if (!txp)
		return -ENOMEM;
	dp->tx_private = txp;
	for (i = 0; i < dev->num_tx_queues; i++,txp++) {
		txp->txqnum = i;
		txp->dev = dev;
		__skb_queue_head_init(&txp->rq);
		__skb_queue_head_init(&txp->tq);
		u64_stats_init(&txp->rsync);
		u64_stats_init(&txp->tsync);
		tasklet_init(&txp->ifb_tasklet, ifb_ri_tasklet,
			     (unsigned long)txp);
		netif_tx_start_queue(netdev_get_tx_queue(dev, i));
	}
	return 0;
}