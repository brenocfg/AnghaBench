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
struct veth_priv {int /*<<< orphan*/  peer; } ;
struct rtnl_link_stats64 {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; void* rx_dropped; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; void* tx_dropped; } ;
struct pcpu_vstats {int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct veth_priv* netdev_priv (struct net_device*) ; 
 struct net_device* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 void* veth_stats_one (struct pcpu_vstats*,struct net_device*) ; 

__attribute__((used)) static void veth_get_stats64(struct net_device *dev,
			     struct rtnl_link_stats64 *tot)
{
	struct veth_priv *priv = netdev_priv(dev);
	struct net_device *peer;
	struct pcpu_vstats one;

	tot->tx_dropped = veth_stats_one(&one, dev);
	tot->tx_bytes = one.bytes;
	tot->tx_packets = one.packets;

	rcu_read_lock();
	peer = rcu_dereference(priv->peer);
	if (peer) {
		tot->rx_dropped = veth_stats_one(&one, peer);
		tot->rx_bytes = one.bytes;
		tot->rx_packets = one.packets;
	}
	rcu_read_unlock();
}