#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rhine_private {int /*<<< orphan*/ ** rx_skbuff; int /*<<< orphan*/  rx_buf_sz; int /*<<< orphan*/ * rx_skbuff_dma; TYPE_1__* rx_ring; } ;
struct TYPE_4__ {struct device* parent; } ;
struct net_device {TYPE_2__ dev; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; scalar_t__ rx_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rhine_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void free_rbufs(struct net_device* dev)
{
	struct rhine_private *rp = netdev_priv(dev);
	struct device *hwdev = dev->dev.parent;
	int i;

	/* Free all the skbuffs in the Rx queue. */
	for (i = 0; i < RX_RING_SIZE; i++) {
		rp->rx_ring[i].rx_status = 0;
		rp->rx_ring[i].addr = cpu_to_le32(0xBADF00D0); /* An invalid address. */
		if (rp->rx_skbuff[i]) {
			dma_unmap_single(hwdev,
					 rp->rx_skbuff_dma[i],
					 rp->rx_buf_sz, DMA_FROM_DEVICE);
			dev_kfree_skb(rp->rx_skbuff[i]);
		}
		rp->rx_skbuff[i] = NULL;
	}
}