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
typedef  int /*<<< orphan*/  u32 ;
struct xlgmac_pdata {unsigned int channel_count; unsigned int tx_q_count; struct xlgmac_channel* channel_head; scalar_t__ mac_regs; } ;
struct xlgmac_channel {int /*<<< orphan*/  tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_TCR ; 
 int /*<<< orphan*/  DMA_CH_TCR_ST_LEN ; 
 int /*<<< orphan*/  DMA_CH_TCR_ST_POS ; 
 scalar_t__ MAC_TCR ; 
 int /*<<< orphan*/  MAC_TCR_TE_LEN ; 
 int /*<<< orphan*/  MAC_TCR_TE_POS ; 
 int /*<<< orphan*/  MTL_Q_TQOMR ; 
 int /*<<< orphan*/  MTL_Q_TQOMR_TXQEN_LEN ; 
 int /*<<< orphan*/  MTL_Q_TQOMR_TXQEN_POS ; 
 scalar_t__ XLGMAC_DMA_REG (struct xlgmac_channel*,int /*<<< orphan*/ ) ; 
 scalar_t__ XLGMAC_MTL_REG (struct xlgmac_pdata*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLGMAC_SET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xlgmac_prepare_tx_stop (struct xlgmac_pdata*,struct xlgmac_channel*) ; 

__attribute__((used)) static void xlgmac_disable_tx(struct xlgmac_pdata *pdata)
{
	struct xlgmac_channel *channel;
	unsigned int i;
	u32 regval;

	/* Prepare for Tx DMA channel stop */
	channel = pdata->channel_head;
	for (i = 0; i < pdata->channel_count; i++, channel++) {
		if (!channel->tx_ring)
			break;

		xlgmac_prepare_tx_stop(pdata, channel);
	}

	/* Disable MAC Tx */
	regval = readl(pdata->mac_regs + MAC_TCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_TCR_TE_POS,
				     MAC_TCR_TE_LEN, 0);
	writel(regval, pdata->mac_regs + MAC_TCR);

	/* Disable each Tx queue */
	for (i = 0; i < pdata->tx_q_count; i++) {
		regval = readl(XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_TQOMR_TXQEN_POS,
					     MTL_Q_TQOMR_TXQEN_LEN, 0);
		writel(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
	}

	/* Disable each Tx DMA channel */
	channel = pdata->channel_head;
	for (i = 0; i < pdata->channel_count; i++, channel++) {
		if (!channel->tx_ring)
			break;

		regval = readl(XLGMAC_DMA_REG(channel, DMA_CH_TCR));
		regval = XLGMAC_SET_REG_BITS(regval, DMA_CH_TCR_ST_POS,
					     DMA_CH_TCR_ST_LEN, 0);
		writel(regval, XLGMAC_DMA_REG(channel, DMA_CH_TCR));
	}
}