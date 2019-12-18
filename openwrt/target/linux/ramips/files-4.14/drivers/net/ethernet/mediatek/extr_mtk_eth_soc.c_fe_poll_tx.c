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
typedef  size_t u32 ;
struct sk_buff {scalar_t__ len; } ;
struct device {int dummy; } ;
struct net_device {struct device dev; } ;
struct fe_tx_ring {size_t tx_free_idx; scalar_t__ tx_thresh; struct fe_tx_buf* tx_buf; } ;
struct fe_tx_buf {struct sk_buff* skb; } ;
struct fe_priv {struct fe_tx_ring tx_ring; struct net_device* netdev; } ;

/* Variables and functions */
 scalar_t__ DMA_DUMMY_DESC ; 
 int /*<<< orphan*/  FE_REG_FE_INT_STATUS ; 
 int /*<<< orphan*/  FE_REG_TX_DTX_IDX0 ; 
 size_t NEXT_TX_DESP_IDX (size_t) ; 
 scalar_t__ fe_empty_txd (struct fe_tx_ring*) ; 
 size_t fe_reg_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_reg_w32 (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_txd_unmap (struct device*,struct fe_tx_buf*) ; 
 int /*<<< orphan*/  netdev_completed_queue (struct net_device*,int,unsigned int) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int fe_poll_tx(struct fe_priv *priv, int budget, u32 tx_intr,
		      int *tx_again)
{
	struct net_device *netdev = priv->netdev;
	struct device *dev = &netdev->dev;
	unsigned int bytes_compl = 0;
	struct sk_buff *skb;
	struct fe_tx_buf *tx_buf;
	int done = 0;
	u32 idx, hwidx;
	struct fe_tx_ring *ring = &priv->tx_ring;

	idx = ring->tx_free_idx;
	hwidx = fe_reg_r32(FE_REG_TX_DTX_IDX0);

	while ((idx != hwidx) && budget) {
		tx_buf = &ring->tx_buf[idx];
		skb = tx_buf->skb;

		if (!skb)
			break;

		if (skb != (struct sk_buff *)DMA_DUMMY_DESC) {
			bytes_compl += skb->len;
			done++;
			budget--;
		}
		fe_txd_unmap(dev, tx_buf);
		idx = NEXT_TX_DESP_IDX(idx);
	}
	ring->tx_free_idx = idx;

	if (idx == hwidx) {
		/* read hw index again make sure no new tx packet */
		hwidx = fe_reg_r32(FE_REG_TX_DTX_IDX0);
		if (idx == hwidx)
			fe_reg_w32(tx_intr, FE_REG_FE_INT_STATUS);
		else
			*tx_again = 1;
	} else {
		*tx_again = 1;
	}

	if (done) {
		netdev_completed_queue(netdev, done, bytes_compl);
		smp_mb();
		if (unlikely(netif_queue_stopped(netdev) &&
			     (fe_empty_txd(ring) > ring->tx_thresh)))
			netif_wake_queue(netdev);
	}

	return done;
}