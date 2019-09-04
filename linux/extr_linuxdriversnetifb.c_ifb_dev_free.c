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
struct ifb_q_private {int /*<<< orphan*/  tq; int /*<<< orphan*/  rq; int /*<<< orphan*/  ifb_tasklet; } ;
struct ifb_dev_private {struct ifb_q_private* tx_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ifb_q_private*) ; 
 struct ifb_dev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ifb_dev_free(struct net_device *dev)
{
	struct ifb_dev_private *dp = netdev_priv(dev);
	struct ifb_q_private *txp = dp->tx_private;
	int i;

	for (i = 0; i < dev->num_tx_queues; i++,txp++) {
		tasklet_kill(&txp->ifb_tasklet);
		__skb_queue_purge(&txp->rq);
		__skb_queue_purge(&txp->tq);
	}
	kfree(dp->tx_private);
}