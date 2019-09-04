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
struct stmmac_rx_queue {scalar_t__ dma_rx; scalar_t__ dma_erx; } ;
struct stmmac_priv {scalar_t__ extend_desc; struct stmmac_rx_queue* rx_queue; TYPE_1__* plat; } ;
struct TYPE_2__ {size_t rx_queues_to_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RX_SIZE ; 
 int /*<<< orphan*/  pr_info (char*,size_t) ; 
 int /*<<< orphan*/  stmmac_display_ring (struct stmmac_priv*,void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stmmac_display_rx_rings(struct stmmac_priv *priv)
{
	u32 rx_cnt = priv->plat->rx_queues_to_use;
	void *head_rx;
	u32 queue;

	/* Display RX rings */
	for (queue = 0; queue < rx_cnt; queue++) {
		struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];

		pr_info("\tRX Queue %u rings\n", queue);

		if (priv->extend_desc)
			head_rx = (void *)rx_q->dma_erx;
		else
			head_rx = (void *)rx_q->dma_rx;

		/* Display RX ring */
		stmmac_display_ring(priv, head_rx, DMA_RX_SIZE, true);
	}
}