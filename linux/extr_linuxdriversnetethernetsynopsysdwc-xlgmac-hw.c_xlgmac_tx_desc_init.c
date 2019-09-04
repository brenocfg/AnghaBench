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
struct xlgmac_ring {int cur; int dma_desc_count; } ;
struct xlgmac_desc_data {int /*<<< orphan*/  dma_desc_addr; } ;
struct xlgmac_channel {struct xlgmac_ring* tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_TDLR_HI ; 
 int /*<<< orphan*/  DMA_CH_TDLR_LO ; 
 int /*<<< orphan*/  DMA_CH_TDRLR ; 
 int /*<<< orphan*/  XLGMAC_DMA_REG (struct xlgmac_channel*,int /*<<< orphan*/ ) ; 
 struct xlgmac_desc_data* XLGMAC_GET_DESC_DATA (struct xlgmac_ring*,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlgmac_tx_desc_reset (struct xlgmac_desc_data*) ; 

__attribute__((used)) static void xlgmac_tx_desc_init(struct xlgmac_channel *channel)
{
	struct xlgmac_ring *ring = channel->tx_ring;
	struct xlgmac_desc_data *desc_data;
	int start_index = ring->cur;
	int i;

	/* Initialze all descriptors */
	for (i = 0; i < ring->dma_desc_count; i++) {
		desc_data = XLGMAC_GET_DESC_DATA(ring, i);

		/* Initialize Tx descriptor */
		xlgmac_tx_desc_reset(desc_data);
	}

	/* Update the total number of Tx descriptors */
	writel(ring->dma_desc_count - 1, XLGMAC_DMA_REG(channel, DMA_CH_TDRLR));

	/* Update the starting address of descriptor ring */
	desc_data = XLGMAC_GET_DESC_DATA(ring, start_index);
	writel(upper_32_bits(desc_data->dma_desc_addr),
	       XLGMAC_DMA_REG(channel, DMA_CH_TDLR_HI));
	writel(lower_32_bits(desc_data->dma_desc_addr),
	       XLGMAC_DMA_REG(channel, DMA_CH_TDLR_LO));
}