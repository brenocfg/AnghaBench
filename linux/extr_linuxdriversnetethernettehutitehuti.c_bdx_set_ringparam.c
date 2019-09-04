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
struct net_device {int dummy; } ;
struct ethtool_ringparam {scalar_t__ rx_pending; scalar_t__ tx_pending; } ;
struct bdx_priv {int rxf_size; int txd_size; int rxd_size; int txf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  bdx_close (struct net_device*) ; 
 int /*<<< orphan*/  bdx_open (struct net_device*) ; 
 scalar_t__ bdx_rx_fifo_size_to_packets (int) ; 
 scalar_t__ bdx_tx_fifo_size_to_packets (int) ; 
 struct bdx_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int
bdx_set_ringparam(struct net_device *netdev, struct ethtool_ringparam *ring)
{
	struct bdx_priv *priv = netdev_priv(netdev);
	int rx_size = 0;
	int tx_size = 0;

	for (; rx_size < 4; rx_size++) {
		if (bdx_rx_fifo_size_to_packets(rx_size) >= ring->rx_pending)
			break;
	}
	if (rx_size == 4)
		rx_size = 3;

	for (; tx_size < 4; tx_size++) {
		if (bdx_tx_fifo_size_to_packets(tx_size) >= ring->tx_pending)
			break;
	}
	if (tx_size == 4)
		tx_size = 3;

	/*Is there anything to do? */
	if ((rx_size == priv->rxf_size) &&
	    (tx_size == priv->txd_size))
		return 0;

	priv->rxf_size = rx_size;
	if (rx_size > 1)
		priv->rxd_size = rx_size - 1;
	else
		priv->rxd_size = rx_size;

	priv->txf_size = priv->txd_size = tx_size;

	if (netif_running(netdev)) {
		bdx_close(netdev);
		bdx_open(netdev);
	}
	return 0;
}