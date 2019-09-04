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
struct stmmac_rx_queue {int dirty_rx; scalar_t__ dma_rx_phy; struct stmmac_priv* priv_data; } ;
struct stmmac_priv {int /*<<< orphan*/  extend_desc; scalar_t__ hwts_rx_en; } ;
struct dma_desc {int /*<<< orphan*/  des3; } ;

/* Variables and functions */
 int DMA_RX_SIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 

__attribute__((used)) static void refill_desc3(void *priv_ptr, struct dma_desc *p)
{
	struct stmmac_rx_queue *rx_q = (struct stmmac_rx_queue *)priv_ptr;
	struct stmmac_priv *priv = rx_q->priv_data;

	if (priv->hwts_rx_en && !priv->extend_desc)
		/* NOTE: Device will overwrite des3 with timestamp value if
		 * 1588-2002 time stamping is enabled, hence reinitialize it
		 * to keep explicit chaining in the descriptor.
		 */
		p->des3 = cpu_to_le32((unsigned int)(rx_q->dma_rx_phy +
				      (((rx_q->dirty_rx) + 1) %
				       DMA_RX_SIZE) *
				      sizeof(struct dma_desc)));
}