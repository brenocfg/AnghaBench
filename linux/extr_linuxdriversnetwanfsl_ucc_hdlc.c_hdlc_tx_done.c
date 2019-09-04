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
typedef  int u16 ;
struct ucc_hdlc_private {size_t skb_dirtytx; struct qe_bd* dirty_tx; struct qe_bd* tx_bd_base; struct sk_buff** tx_skbuff; scalar_t__ dma_tx_addr; scalar_t__ tx_buffer; struct net_device* ndev; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct qe_bd {int /*<<< orphan*/  status; int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_BD_RING_LEN ; 
 int TX_RING_MOD_MASK (int /*<<< orphan*/ ) ; 
 int T_R_S ; 
 int T_W_S ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int ioread16be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static int hdlc_tx_done(struct ucc_hdlc_private *priv)
{
	/* Start from the next BD that should be filled */
	struct net_device *dev = priv->ndev;
	struct qe_bd *bd;		/* BD pointer */
	u16 bd_status;

	bd = priv->dirty_tx;
	bd_status = ioread16be(&bd->status);

	/* Normal processing. */
	while ((bd_status & T_R_S) == 0) {
		struct sk_buff *skb;

		/* BD contains already transmitted buffer.   */
		/* Handle the transmitted buffer and release */
		/* the BD to be used with the current frame  */

		skb = priv->tx_skbuff[priv->skb_dirtytx];
		if (!skb)
			break;
		dev->stats.tx_packets++;
		memset(priv->tx_buffer +
		       (be32_to_cpu(bd->buf) - priv->dma_tx_addr),
		       0, skb->len);
		dev_kfree_skb_irq(skb);

		priv->tx_skbuff[priv->skb_dirtytx] = NULL;
		priv->skb_dirtytx =
		    (priv->skb_dirtytx +
		     1) & TX_RING_MOD_MASK(TX_BD_RING_LEN);

		/* We freed a buffer, so now we can restart transmission */
		if (netif_queue_stopped(dev))
			netif_wake_queue(dev);

		/* Advance the confirmation BD pointer */
		if (!(bd_status & T_W_S))
			bd += 1;
		else
			bd = priv->tx_bd_base;
		bd_status = ioread16be(&bd->status);
	}
	priv->dirty_tx = bd;

	return 0;
}