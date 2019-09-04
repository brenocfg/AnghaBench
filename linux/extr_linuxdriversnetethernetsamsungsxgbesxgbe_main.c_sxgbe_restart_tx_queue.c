#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sxgbe_tx_queue {scalar_t__ dirty_tx; scalar_t__ cur_tx; } ;
struct sxgbe_priv_data {TYPE_4__* dev; int /*<<< orphan*/  ioaddr; TYPE_2__* hw; struct sxgbe_tx_queue** txq; } ;
struct netdev_queue {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_errors; } ;
struct TYPE_8__ {TYPE_3__ stats; } ;
struct TYPE_6__ {TYPE_1__* dma; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* start_tx_queue ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* stop_tx_queue ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 struct netdev_queue* netdev_get_tx_queue (TYPE_4__*,int) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tx_free_ring_skbufs (struct sxgbe_tx_queue*) ; 

__attribute__((used)) static void sxgbe_restart_tx_queue(struct sxgbe_priv_data *priv, int queue_num)
{
	struct sxgbe_tx_queue *tx_ring = priv->txq[queue_num];
	struct netdev_queue *dev_txq = netdev_get_tx_queue(priv->dev,
							   queue_num);

	/* stop the queue */
	netif_tx_stop_queue(dev_txq);

	/* stop the tx dma */
	priv->hw->dma->stop_tx_queue(priv->ioaddr, queue_num);

	/* free the skbuffs of the ring */
	tx_free_ring_skbufs(tx_ring);

	/* initialise counters */
	tx_ring->cur_tx = 0;
	tx_ring->dirty_tx = 0;

	/* start the tx dma */
	priv->hw->dma->start_tx_queue(priv->ioaddr, queue_num);

	priv->dev->stats.tx_errors++;

	/* wakeup the queue */
	netif_tx_wake_queue(dev_txq);
}