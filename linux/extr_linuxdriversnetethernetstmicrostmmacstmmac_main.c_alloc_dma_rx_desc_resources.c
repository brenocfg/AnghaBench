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
typedef  size_t u32 ;
struct stmmac_rx_queue {size_t queue_index; void* dma_rx; int /*<<< orphan*/  dma_rx_phy; void* dma_erx; void* rx_skbuff; void* rx_skbuff_dma; struct stmmac_priv* priv_data; } ;
struct stmmac_priv {int /*<<< orphan*/  device; scalar_t__ extend_desc; struct stmmac_rx_queue* rx_queue; TYPE_1__* plat; } ;
struct sk_buff {int dummy; } ;
struct dma_extended_desc {int dummy; } ;
struct dma_desc {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {size_t rx_queues_to_use; } ;

/* Variables and functions */
 int DMA_RX_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_zalloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dma_rx_desc_resources (struct stmmac_priv*) ; 
 void* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_dma_rx_desc_resources(struct stmmac_priv *priv)
{
	u32 rx_count = priv->plat->rx_queues_to_use;
	int ret = -ENOMEM;
	u32 queue;

	/* RX queues buffers and DMA */
	for (queue = 0; queue < rx_count; queue++) {
		struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];

		rx_q->queue_index = queue;
		rx_q->priv_data = priv;

		rx_q->rx_skbuff_dma = kmalloc_array(DMA_RX_SIZE,
						    sizeof(dma_addr_t),
						    GFP_KERNEL);
		if (!rx_q->rx_skbuff_dma)
			goto err_dma;

		rx_q->rx_skbuff = kmalloc_array(DMA_RX_SIZE,
						sizeof(struct sk_buff *),
						GFP_KERNEL);
		if (!rx_q->rx_skbuff)
			goto err_dma;

		if (priv->extend_desc) {
			rx_q->dma_erx = dma_zalloc_coherent(priv->device,
							    DMA_RX_SIZE *
							    sizeof(struct
							    dma_extended_desc),
							    &rx_q->dma_rx_phy,
							    GFP_KERNEL);
			if (!rx_q->dma_erx)
				goto err_dma;

		} else {
			rx_q->dma_rx = dma_zalloc_coherent(priv->device,
							   DMA_RX_SIZE *
							   sizeof(struct
							   dma_desc),
							   &rx_q->dma_rx_phy,
							   GFP_KERNEL);
			if (!rx_q->dma_rx)
				goto err_dma;
		}
	}

	return 0;

err_dma:
	free_dma_rx_desc_resources(priv);

	return ret;
}