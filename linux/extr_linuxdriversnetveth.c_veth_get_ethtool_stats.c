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
struct veth_priv {int /*<<< orphan*/  peer; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 struct veth_priv* netdev_priv (struct net_device*) ; 
 struct net_device* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void veth_get_ethtool_stats(struct net_device *dev,
		struct ethtool_stats *stats, u64 *data)
{
	struct veth_priv *priv = netdev_priv(dev);
	struct net_device *peer = rtnl_dereference(priv->peer);

	data[0] = peer ? peer->ifindex : 0;
}