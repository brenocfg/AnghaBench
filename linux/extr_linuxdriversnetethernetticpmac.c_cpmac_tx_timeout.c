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
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct cpmac_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  reset_pending; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  cpmac_clear_tx (struct net_device*) ; 
 scalar_t__ net_ratelimit () ; 
 struct cpmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 scalar_t__ netif_msg_tx_err (struct cpmac_priv*) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpmac_tx_timeout(struct net_device *dev)
{
	struct cpmac_priv *priv = netdev_priv(dev);

	spin_lock(&priv->lock);
	dev->stats.tx_errors++;
	spin_unlock(&priv->lock);
	if (netif_msg_tx_err(priv) && net_ratelimit())
		netdev_warn(dev, "transmit timeout\n");

	atomic_inc(&priv->reset_pending);
	barrier();
	cpmac_clear_tx(dev);
	barrier();
	atomic_dec(&priv->reset_pending);

	netif_tx_wake_all_queues(priv->dev);
}