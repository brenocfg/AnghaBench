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
struct xlgmac_ring {scalar_t__ dirty; scalar_t__ cur; } ;
struct xlgmac_hw_ops {int /*<<< orphan*/  (* rx_desc_reset ) (struct xlgmac_pdata*,struct xlgmac_desc_data*,scalar_t__) ;} ;
struct xlgmac_desc_ops {scalar_t__ (* map_rx_buffer ) (struct xlgmac_pdata*,struct xlgmac_ring*,struct xlgmac_desc_data*) ;int /*<<< orphan*/  (* unmap_desc_data ) (struct xlgmac_pdata*,struct xlgmac_desc_data*) ;} ;
struct xlgmac_pdata {struct xlgmac_hw_ops hw_ops; struct xlgmac_desc_ops desc_ops; } ;
struct xlgmac_desc_data {int /*<<< orphan*/  dma_desc_addr; } ;
struct xlgmac_channel {struct xlgmac_ring* rx_ring; struct xlgmac_pdata* pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_RDTR_LO ; 
 int /*<<< orphan*/  XLGMAC_DMA_REG (struct xlgmac_channel*,int /*<<< orphan*/ ) ; 
 struct xlgmac_desc_data* XLGMAC_GET_DESC_DATA (struct xlgmac_ring*,scalar_t__) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xlgmac_pdata*,struct xlgmac_desc_data*) ; 
 scalar_t__ stub2 (struct xlgmac_pdata*,struct xlgmac_ring*,struct xlgmac_desc_data*) ; 
 int /*<<< orphan*/  stub3 (struct xlgmac_pdata*,struct xlgmac_desc_data*,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xlgmac_rx_refresh(struct xlgmac_channel *channel)
{
	struct xlgmac_pdata *pdata = channel->pdata;
	struct xlgmac_ring *ring = channel->rx_ring;
	struct xlgmac_desc_data *desc_data;
	struct xlgmac_desc_ops *desc_ops;
	struct xlgmac_hw_ops *hw_ops;

	desc_ops = &pdata->desc_ops;
	hw_ops = &pdata->hw_ops;

	while (ring->dirty != ring->cur) {
		desc_data = XLGMAC_GET_DESC_DATA(ring, ring->dirty);

		/* Reset desc_data values */
		desc_ops->unmap_desc_data(pdata, desc_data);

		if (desc_ops->map_rx_buffer(pdata, ring, desc_data))
			break;

		hw_ops->rx_desc_reset(pdata, desc_data, ring->dirty);

		ring->dirty++;
	}

	/* Make sure everything is written before the register write */
	wmb();

	/* Update the Rx Tail Pointer Register with address of
	 * the last cleaned entry
	 */
	desc_data = XLGMAC_GET_DESC_DATA(ring, ring->dirty - 1);
	writel(lower_32_bits(desc_data->dma_desc_addr),
	       XLGMAC_DMA_REG(channel, DMA_CH_RDTR_LO));
}