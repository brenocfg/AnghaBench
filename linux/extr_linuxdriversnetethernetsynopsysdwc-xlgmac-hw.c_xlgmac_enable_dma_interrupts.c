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
struct xlgmac_pdata {unsigned int channel_count; int /*<<< orphan*/  per_channel_irq; struct xlgmac_channel* channel_head; } ;
struct xlgmac_channel {scalar_t__ rx_ring; scalar_t__ tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_IER ; 
 int /*<<< orphan*/  DMA_CH_IER_AIE_LEN ; 
 int /*<<< orphan*/  DMA_CH_IER_AIE_POS ; 
 int /*<<< orphan*/  DMA_CH_IER_FBEE_LEN ; 
 int /*<<< orphan*/  DMA_CH_IER_FBEE_POS ; 
 int /*<<< orphan*/  DMA_CH_IER_NIE_LEN ; 
 int /*<<< orphan*/  DMA_CH_IER_NIE_POS ; 
 int /*<<< orphan*/  DMA_CH_IER_RBUE_LEN ; 
 int /*<<< orphan*/  DMA_CH_IER_RBUE_POS ; 
 int /*<<< orphan*/  DMA_CH_IER_RIE_LEN ; 
 int /*<<< orphan*/  DMA_CH_IER_RIE_POS ; 
 int /*<<< orphan*/  DMA_CH_IER_TIE_LEN ; 
 int /*<<< orphan*/  DMA_CH_IER_TIE_POS ; 
 int /*<<< orphan*/  DMA_CH_SR ; 
 int /*<<< orphan*/  XLGMAC_DMA_REG (struct xlgmac_channel*,int /*<<< orphan*/ ) ; 
 unsigned int XLGMAC_SET_REG_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xlgmac_enable_dma_interrupts(struct xlgmac_pdata *pdata)
{
	unsigned int dma_ch_isr, dma_ch_ier;
	struct xlgmac_channel *channel;
	unsigned int i;

	channel = pdata->channel_head;
	for (i = 0; i < pdata->channel_count; i++, channel++) {
		/* Clear all the interrupts which are set */
		dma_ch_isr = readl(XLGMAC_DMA_REG(channel, DMA_CH_SR));
		writel(dma_ch_isr, XLGMAC_DMA_REG(channel, DMA_CH_SR));

		/* Clear all interrupt enable bits */
		dma_ch_ier = 0;

		/* Enable following interrupts
		 *   NIE  - Normal Interrupt Summary Enable
		 *   AIE  - Abnormal Interrupt Summary Enable
		 *   FBEE - Fatal Bus Error Enable
		 */
		dma_ch_ier = XLGMAC_SET_REG_BITS(dma_ch_ier,
						 DMA_CH_IER_NIE_POS,
					DMA_CH_IER_NIE_LEN, 1);
		dma_ch_ier = XLGMAC_SET_REG_BITS(dma_ch_ier,
						 DMA_CH_IER_AIE_POS,
					DMA_CH_IER_AIE_LEN, 1);
		dma_ch_ier = XLGMAC_SET_REG_BITS(dma_ch_ier,
						 DMA_CH_IER_FBEE_POS,
					DMA_CH_IER_FBEE_LEN, 1);

		if (channel->tx_ring) {
			/* Enable the following Tx interrupts
			 *   TIE  - Transmit Interrupt Enable (unless using
			 *          per channel interrupts)
			 */
			if (!pdata->per_channel_irq)
				dma_ch_ier = XLGMAC_SET_REG_BITS(
						dma_ch_ier,
						DMA_CH_IER_TIE_POS,
						DMA_CH_IER_TIE_LEN,
						1);
		}
		if (channel->rx_ring) {
			/* Enable following Rx interrupts
			 *   RBUE - Receive Buffer Unavailable Enable
			 *   RIE  - Receive Interrupt Enable (unless using
			 *          per channel interrupts)
			 */
			dma_ch_ier = XLGMAC_SET_REG_BITS(
					dma_ch_ier,
					DMA_CH_IER_RBUE_POS,
					DMA_CH_IER_RBUE_LEN,
					1);
			if (!pdata->per_channel_irq)
				dma_ch_ier = XLGMAC_SET_REG_BITS(
						dma_ch_ier,
						DMA_CH_IER_RIE_POS,
						DMA_CH_IER_RIE_LEN,
						1);
		}

		writel(dma_ch_isr, XLGMAC_DMA_REG(channel, DMA_CH_IER));
	}
}