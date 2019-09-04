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
struct tx_desc {int dummy; } ;
struct rx_desc {int dummy; } ;
struct rhine_private {int /*<<< orphan*/ * tx_bufs; int /*<<< orphan*/  tx_bufs_dma; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/  rx_ring_dma; int /*<<< orphan*/ * rx_ring; } ;
struct TYPE_2__ {struct device* parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int PKT_BUF_SZ ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rhine_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void free_ring(struct net_device* dev)
{
	struct rhine_private *rp = netdev_priv(dev);
	struct device *hwdev = dev->dev.parent;

	dma_free_coherent(hwdev,
			  RX_RING_SIZE * sizeof(struct rx_desc) +
			  TX_RING_SIZE * sizeof(struct tx_desc),
			  rp->rx_ring, rp->rx_ring_dma);
	rp->tx_ring = NULL;

	if (rp->tx_bufs)
		dma_free_coherent(hwdev, PKT_BUF_SZ * TX_RING_SIZE,
				  rp->tx_bufs, rp->tx_bufs_dma);

	rp->tx_bufs = NULL;

}