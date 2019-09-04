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
struct sh_eth_private {int /*<<< orphan*/  dirty_tx; int /*<<< orphan*/  dirty_rx; int /*<<< orphan*/  cur_tx; int /*<<< orphan*/  cur_rx; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 struct sh_eth_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void sh_eth_get_ethtool_stats(struct net_device *ndev,
				     struct ethtool_stats *stats, u64 *data)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	int i = 0;

	/* device-specific stats */
	data[i++] = mdp->cur_rx;
	data[i++] = mdp->cur_tx;
	data[i++] = mdp->dirty_rx;
	data[i++] = mdp->dirty_tx;
}