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
struct temac_local {int rx_bd_ci; int temac_features; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  (* dma_out ) (struct temac_local*,int /*<<< orphan*/ ,scalar_t__) ;struct cdmac_bd* rx_bd_v; struct sk_buff** rx_skb; scalar_t__ rx_bd_p; } ;
struct sk_buff {scalar_t__ protocol; int len; int csum; int /*<<< orphan*/  data; int /*<<< orphan*/  ip_summed; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {int rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_2__ dev; TYPE_1__ stats; } ;
struct cdmac_bd {unsigned int app0; int app4; int app3; int /*<<< orphan*/  len; int /*<<< orphan*/  phys; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_COMPLETE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 size_t RX_BD_NUM ; 
 int /*<<< orphan*/  RX_TAILDESC_PTR ; 
 unsigned int STS_CTRL_APP0_CMPLT ; 
 unsigned int STS_CTRL_APP0_IRQONEND ; 
 int TEMAC_FEATURE_RX_CSUM ; 
 int /*<<< orphan*/  XTE_MAX_JUMBO_FRAME_SIZE ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,int /*<<< orphan*/ ) ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_defer_rx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct temac_local*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ll_temac_recv(struct net_device *ndev)
{
	struct temac_local *lp = netdev_priv(ndev);
	struct sk_buff *skb, *new_skb;
	unsigned int bdstat;
	struct cdmac_bd *cur_p;
	dma_addr_t tail_p;
	int length;
	unsigned long flags;

	spin_lock_irqsave(&lp->rx_lock, flags);

	tail_p = lp->rx_bd_p + sizeof(*lp->rx_bd_v) * lp->rx_bd_ci;
	cur_p = &lp->rx_bd_v[lp->rx_bd_ci];

	bdstat = cur_p->app0;
	while ((bdstat & STS_CTRL_APP0_CMPLT)) {

		skb = lp->rx_skb[lp->rx_bd_ci];
		length = cur_p->app4 & 0x3FFF;

		dma_unmap_single(ndev->dev.parent, cur_p->phys, length,
				 DMA_FROM_DEVICE);

		skb_put(skb, length);
		skb->protocol = eth_type_trans(skb, ndev);
		skb_checksum_none_assert(skb);

		/* if we're doing rx csum offload, set it up */
		if (((lp->temac_features & TEMAC_FEATURE_RX_CSUM) != 0) &&
		    (skb->protocol == htons(ETH_P_IP)) &&
		    (skb->len > 64)) {

			skb->csum = cur_p->app3 & 0xFFFF;
			skb->ip_summed = CHECKSUM_COMPLETE;
		}

		if (!skb_defer_rx_timestamp(skb))
			netif_rx(skb);

		ndev->stats.rx_packets++;
		ndev->stats.rx_bytes += length;

		new_skb = netdev_alloc_skb_ip_align(ndev,
						XTE_MAX_JUMBO_FRAME_SIZE);
		if (!new_skb) {
			spin_unlock_irqrestore(&lp->rx_lock, flags);
			return;
		}

		cur_p->app0 = STS_CTRL_APP0_IRQONEND;
		cur_p->phys = dma_map_single(ndev->dev.parent, new_skb->data,
					     XTE_MAX_JUMBO_FRAME_SIZE,
					     DMA_FROM_DEVICE);
		cur_p->len = XTE_MAX_JUMBO_FRAME_SIZE;
		lp->rx_skb[lp->rx_bd_ci] = new_skb;

		lp->rx_bd_ci++;
		if (lp->rx_bd_ci >= RX_BD_NUM)
			lp->rx_bd_ci = 0;

		cur_p = &lp->rx_bd_v[lp->rx_bd_ci];
		bdstat = cur_p->app0;
	}
	lp->dma_out(lp, RX_TAILDESC_PTR, tail_p);

	spin_unlock_irqrestore(&lp->rx_lock, flags);
}