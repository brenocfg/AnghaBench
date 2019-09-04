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
struct stmmac_rx_queue {unsigned int dirty_rx; scalar_t__ rx_zeroc_thresh; int /*<<< orphan*/ * rx_skbuff_dma; struct sk_buff** rx_skbuff; struct dma_desc* dma_rx; scalar_t__ dma_erx; } ;
struct stmmac_priv {int dma_buf_sz; int /*<<< orphan*/  use_riwt; int /*<<< orphan*/  dev; int /*<<< orphan*/  device; scalar_t__ extend_desc; struct stmmac_rx_queue* rx_queue; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct dma_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_RX_SIZE ; 
 unsigned int STMMAC_GET_ENTRY (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ STMMAC_RX_THRESH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 scalar_t__ likely (int) ; 
 int net_ratelimit () ; 
 struct sk_buff* netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_dbg (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  rx_status ; 
 int /*<<< orphan*/  stmmac_refill_desc3 (struct stmmac_priv*,struct stmmac_rx_queue*,struct dma_desc*) ; 
 int stmmac_rx_dirty (struct stmmac_priv*,size_t) ; 
 int /*<<< orphan*/  stmmac_set_desc_addr (struct stmmac_priv*,struct dma_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_set_rx_owner (struct stmmac_priv*,struct dma_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void stmmac_rx_refill(struct stmmac_priv *priv, u32 queue)
{
	struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];
	int dirty = stmmac_rx_dirty(priv, queue);
	unsigned int entry = rx_q->dirty_rx;

	int bfsize = priv->dma_buf_sz;

	while (dirty-- > 0) {
		struct dma_desc *p;

		if (priv->extend_desc)
			p = (struct dma_desc *)(rx_q->dma_erx + entry);
		else
			p = rx_q->dma_rx + entry;

		if (likely(!rx_q->rx_skbuff[entry])) {
			struct sk_buff *skb;

			skb = netdev_alloc_skb_ip_align(priv->dev, bfsize);
			if (unlikely(!skb)) {
				/* so for a while no zero-copy! */
				rx_q->rx_zeroc_thresh = STMMAC_RX_THRESH;
				if (unlikely(net_ratelimit()))
					dev_err(priv->device,
						"fail to alloc skb entry %d\n",
						entry);
				break;
			}

			rx_q->rx_skbuff[entry] = skb;
			rx_q->rx_skbuff_dma[entry] =
			    dma_map_single(priv->device, skb->data, bfsize,
					   DMA_FROM_DEVICE);
			if (dma_mapping_error(priv->device,
					      rx_q->rx_skbuff_dma[entry])) {
				netdev_err(priv->dev, "Rx DMA map failed\n");
				dev_kfree_skb(skb);
				break;
			}

			stmmac_set_desc_addr(priv, p, rx_q->rx_skbuff_dma[entry]);
			stmmac_refill_desc3(priv, rx_q, p);

			if (rx_q->rx_zeroc_thresh > 0)
				rx_q->rx_zeroc_thresh--;

			netif_dbg(priv, rx_status, priv->dev,
				  "refill entry #%d\n", entry);
		}
		dma_wmb();

		stmmac_set_rx_owner(priv, p, priv->use_riwt);

		dma_wmb();

		entry = STMMAC_GET_ENTRY(entry, DMA_RX_SIZE);
	}
	rx_q->dirty_rx = entry;
}