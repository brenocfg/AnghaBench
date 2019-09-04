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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {struct device* parent; } ;
struct net_device {int /*<<< orphan*/  max_mtu; int /*<<< orphan*/ * netdev_ops; TYPE_1__ dev; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  mc_token; int /*<<< orphan*/  mc_io; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA2_ETH_MAX_MTU ; 
 int /*<<< orphan*/  DPAA2_ETH_MFL ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dpaa2_eth_ops ; 
 int /*<<< orphan*/  dpaa2_eth_queue_count (struct dpaa2_eth_priv*) ; 
 int dpni_add_mac_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dpni_set_max_frame_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ *) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 
 int netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int set_mac_addr (struct dpaa2_eth_priv*) ; 

__attribute__((used)) static int netdev_init(struct net_device *net_dev)
{
	struct device *dev = net_dev->dev.parent;
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);
	u8 bcast_addr[ETH_ALEN];
	u8 num_queues;
	int err;

	net_dev->netdev_ops = &dpaa2_eth_ops;

	err = set_mac_addr(priv);
	if (err)
		return err;

	/* Explicitly add the broadcast address to the MAC filtering table */
	eth_broadcast_addr(bcast_addr);
	err = dpni_add_mac_addr(priv->mc_io, 0, priv->mc_token, bcast_addr);
	if (err) {
		dev_err(dev, "dpni_add_mac_addr() failed\n");
		return err;
	}

	/* Set MTU upper limit; lower limit is 68B (default value) */
	net_dev->max_mtu = DPAA2_ETH_MAX_MTU;
	err = dpni_set_max_frame_length(priv->mc_io, 0, priv->mc_token,
					DPAA2_ETH_MFL);
	if (err) {
		dev_err(dev, "dpni_set_max_frame_length() failed\n");
		return err;
	}

	/* Set actual number of queues in the net device */
	num_queues = dpaa2_eth_queue_count(priv);
	err = netif_set_real_num_tx_queues(net_dev, num_queues);
	if (err) {
		dev_err(dev, "netif_set_real_num_tx_queues() failed\n");
		return err;
	}
	err = netif_set_real_num_rx_queues(net_dev, num_queues);
	if (err) {
		dev_err(dev, "netif_set_real_num_rx_queues() failed\n");
		return err;
	}

	/* Our .ndo_init will be called herein */
	err = register_netdev(net_dev);
	if (err < 0) {
		dev_err(dev, "register_netdev() failed\n");
		return err;
	}

	return 0;
}