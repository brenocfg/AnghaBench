#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int cntinfo; int /*<<< orphan*/  pbuf; } ;
struct sgiseeq_tx_desc {TYPE_3__ tdma; struct sk_buff* skb; } ;
struct sgiseeq_private {int tx_new; int tx_old; int /*<<< orphan*/  tx_lock; struct sgiseeq_tx_desc* tx_desc; struct hpc3_ethregs* hregs; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {int tx_bytes; } ;
struct net_device {TYPE_2__ dev; TYPE_1__ stats; } ;
struct hpc3_ethregs {int tx_ctrl; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ETH_ZLEN ; 
 int HPC3_ETXCTRL_ACTIVE ; 
 int HPCDMA_BCNT ; 
 int HPCDMA_EOX ; 
 int HPCDMA_EOXP ; 
 int HPCDMA_XIE ; 
 int HPCDMA_XIU ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int NEXT_TX (int) ; 
 size_t PREV_TX (int) ; 
 int /*<<< orphan*/  TX_BUFFS_AVAIL (struct sgiseeq_private*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_desc_cpu (struct net_device*,struct sgiseeq_tx_desc*) ; 
 int /*<<< orphan*/  dma_sync_desc_dev (struct net_device*,struct sgiseeq_tx_desc*) ; 
 int /*<<< orphan*/  kick_tx (struct net_device*,struct sgiseeq_private*,struct hpc3_ethregs*) ; 
 struct sgiseeq_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ skb_padto (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static netdev_tx_t
sgiseeq_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct sgiseeq_private *sp = netdev_priv(dev);
	struct hpc3_ethregs *hregs = sp->hregs;
	unsigned long flags;
	struct sgiseeq_tx_desc *td;
	int len, entry;

	spin_lock_irqsave(&sp->tx_lock, flags);

	/* Setup... */
	len = skb->len;
	if (len < ETH_ZLEN) {
		if (skb_padto(skb, ETH_ZLEN)) {
			spin_unlock_irqrestore(&sp->tx_lock, flags);
			return NETDEV_TX_OK;
		}
		len = ETH_ZLEN;
	}

	dev->stats.tx_bytes += len;
	entry = sp->tx_new;
	td = &sp->tx_desc[entry];
	dma_sync_desc_cpu(dev, td);

	/* Create entry.  There are so many races with adding a new
	 * descriptor to the chain:
	 * 1) Assume that the HPC is off processing a DMA chain while
	 *    we are changing all of the following.
	 * 2) Do no allow the HPC to look at a new descriptor until
	 *    we have completely set up it's state.  This means, do
	 *    not clear HPCDMA_EOX in the current last descritptor
	 *    until the one we are adding looks consistent and could
	 *    be processes right now.
	 * 3) The tx interrupt code must notice when we've added a new
	 *    entry and the HPC got to the end of the chain before we
	 *    added this new entry and restarted it.
	 */
	td->skb = skb;
	td->tdma.pbuf = dma_map_single(dev->dev.parent, skb->data,
				       len, DMA_TO_DEVICE);
	td->tdma.cntinfo = (len & HPCDMA_BCNT) |
	                   HPCDMA_XIU | HPCDMA_EOXP | HPCDMA_XIE | HPCDMA_EOX;
	dma_sync_desc_dev(dev, td);
	if (sp->tx_old != sp->tx_new) {
		struct sgiseeq_tx_desc *backend;

		backend = &sp->tx_desc[PREV_TX(sp->tx_new)];
		dma_sync_desc_cpu(dev, backend);
		backend->tdma.cntinfo &= ~HPCDMA_EOX;
		dma_sync_desc_dev(dev, backend);
	}
	sp->tx_new = NEXT_TX(sp->tx_new); /* Advance. */

	/* Maybe kick the HPC back into motion. */
	if (!(hregs->tx_ctrl & HPC3_ETXCTRL_ACTIVE))
		kick_tx(dev, sp, hregs);

	if (!TX_BUFFS_AVAIL(sp))
		netif_stop_queue(dev);
	spin_unlock_irqrestore(&sp->tx_lock, flags);

	return NETDEV_TX_OK;
}