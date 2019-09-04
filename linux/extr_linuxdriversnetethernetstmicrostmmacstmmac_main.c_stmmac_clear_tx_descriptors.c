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
struct stmmac_tx_queue {int /*<<< orphan*/ * dma_tx; TYPE_1__* dma_etx; } ;
struct stmmac_priv {int /*<<< orphan*/  mode; scalar_t__ extend_desc; struct stmmac_tx_queue* tx_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  basic; } ;

/* Variables and functions */
 int DMA_TX_SIZE ; 
 int /*<<< orphan*/  stmmac_init_tx_desc (struct stmmac_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stmmac_clear_tx_descriptors(struct stmmac_priv *priv, u32 queue)
{
	struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];
	int i;

	/* Clear the TX descriptors */
	for (i = 0; i < DMA_TX_SIZE; i++)
		if (priv->extend_desc)
			stmmac_init_tx_desc(priv, &tx_q->dma_etx[i].basic,
					priv->mode, (i == DMA_TX_SIZE - 1));
		else
			stmmac_init_tx_desc(priv, &tx_q->dma_tx[i],
					priv->mode, (i == DMA_TX_SIZE - 1));
}