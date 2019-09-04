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
typedef  int /*<<< orphan*/  u64 ;
struct sc92031_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  rx_loss; int /*<<< orphan*/  tx_timeouts; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 struct sc92031_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sc92031_ethtool_get_ethtool_stats(struct net_device *dev,
		struct ethtool_stats *stats, u64 *data)
{
	struct sc92031_priv *priv = netdev_priv(dev);

	spin_lock_bh(&priv->lock);
	data[0] = priv->tx_timeouts;
	data[1] = priv->rx_loss;
	spin_unlock_bh(&priv->lock);
}