#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_6__ {int /*<<< orphan*/  buf2_addr; } ;
struct TYPE_7__ {TYPE_1__ rx_rd_des23; } ;
struct sxgbe_rx_norm_desc {TYPE_2__ rdes23; } ;
struct sxgbe_priv_data {unsigned int dma_rx_size; int dma_buf_sz; size_t cur_rx_qnum; TYPE_5__* hw; TYPE_3__** rxq; int /*<<< orphan*/  device; int /*<<< orphan*/  dev; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_4__* desc; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* set_rx_int_on_com ) (struct sxgbe_rx_norm_desc*) ;int /*<<< orphan*/  (* set_rx_owner ) (struct sxgbe_rx_norm_desc*) ;} ;
struct TYPE_8__ {scalar_t__ cur_rx; unsigned int dirty_rx; int /*<<< orphan*/ * rx_skbuff_dma; struct sk_buff** rx_skbuff; struct sxgbe_rx_norm_desc* dma_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct sxgbe_rx_norm_desc*) ; 
 int /*<<< orphan*/  stub2 (struct sxgbe_rx_norm_desc*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void sxgbe_rx_refill(struct sxgbe_priv_data *priv)
{
	unsigned int rxsize = priv->dma_rx_size;
	int bfsize = priv->dma_buf_sz;
	u8 qnum = priv->cur_rx_qnum;

	for (; priv->rxq[qnum]->cur_rx - priv->rxq[qnum]->dirty_rx > 0;
	     priv->rxq[qnum]->dirty_rx++) {
		unsigned int entry = priv->rxq[qnum]->dirty_rx % rxsize;
		struct sxgbe_rx_norm_desc *p;

		p = priv->rxq[qnum]->dma_rx + entry;

		if (likely(priv->rxq[qnum]->rx_skbuff[entry] == NULL)) {
			struct sk_buff *skb;

			skb = netdev_alloc_skb_ip_align(priv->dev, bfsize);

			if (unlikely(skb == NULL))
				break;

			priv->rxq[qnum]->rx_skbuff[entry] = skb;
			priv->rxq[qnum]->rx_skbuff_dma[entry] =
				dma_map_single(priv->device, skb->data, bfsize,
					       DMA_FROM_DEVICE);

			p->rdes23.rx_rd_des23.buf2_addr =
				priv->rxq[qnum]->rx_skbuff_dma[entry];
		}

		/* Added memory barrier for RX descriptor modification */
		wmb();
		priv->hw->desc->set_rx_owner(p);
		priv->hw->desc->set_rx_int_on_com(p);
		/* Added memory barrier for RX descriptor modification */
		wmb();
	}
}