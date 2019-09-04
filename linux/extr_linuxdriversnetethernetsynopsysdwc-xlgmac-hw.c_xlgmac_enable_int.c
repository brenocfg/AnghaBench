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
struct xlgmac_channel {unsigned int saved_ier; } ;
typedef  enum xlgmac_int { ____Placeholder_xlgmac_int } xlgmac_int ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_IER ; 
 int /*<<< orphan*/  DMA_CH_IER_FBEE_LEN ; 
 int /*<<< orphan*/  DMA_CH_IER_FBEE_POS ; 
 int /*<<< orphan*/  DMA_CH_IER_RBUE_LEN ; 
 int /*<<< orphan*/  DMA_CH_IER_RBUE_POS ; 
 int /*<<< orphan*/  DMA_CH_IER_RIE_LEN ; 
 int /*<<< orphan*/  DMA_CH_IER_RIE_POS ; 
 int /*<<< orphan*/  DMA_CH_IER_RSE_LEN ; 
 int /*<<< orphan*/  DMA_CH_IER_RSE_POS ; 
 int /*<<< orphan*/  DMA_CH_IER_TBUE_LEN ; 
 int /*<<< orphan*/  DMA_CH_IER_TBUE_POS ; 
 int /*<<< orphan*/  DMA_CH_IER_TIE_LEN ; 
 int /*<<< orphan*/  DMA_CH_IER_TIE_POS ; 
 int /*<<< orphan*/  DMA_CH_IER_TXSE_LEN ; 
 int /*<<< orphan*/  DMA_CH_IER_TXSE_POS ; 
 int /*<<< orphan*/  XLGMAC_DMA_REG (struct xlgmac_channel*,int /*<<< orphan*/ ) ; 
#define  XLGMAC_INT_DMA_ALL 136 
#define  XLGMAC_INT_DMA_CH_SR_FBE 135 
#define  XLGMAC_INT_DMA_CH_SR_RBU 134 
#define  XLGMAC_INT_DMA_CH_SR_RI 133 
#define  XLGMAC_INT_DMA_CH_SR_RPS 132 
#define  XLGMAC_INT_DMA_CH_SR_TBU 131 
#define  XLGMAC_INT_DMA_CH_SR_TI 130 
#define  XLGMAC_INT_DMA_CH_SR_TI_RI 129 
#define  XLGMAC_INT_DMA_CH_SR_TPS 128 
 unsigned int XLGMAC_SET_REG_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlgmac_enable_int(struct xlgmac_channel *channel,
			     enum xlgmac_int int_id)
{
	unsigned int dma_ch_ier;

	dma_ch_ier = readl(XLGMAC_DMA_REG(channel, DMA_CH_IER));

	switch (int_id) {
	case XLGMAC_INT_DMA_CH_SR_TI:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_TIE_POS,
				DMA_CH_IER_TIE_LEN, 1);
		break;
	case XLGMAC_INT_DMA_CH_SR_TPS:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_TXSE_POS,
				DMA_CH_IER_TXSE_LEN, 1);
		break;
	case XLGMAC_INT_DMA_CH_SR_TBU:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_TBUE_POS,
				DMA_CH_IER_TBUE_LEN, 1);
		break;
	case XLGMAC_INT_DMA_CH_SR_RI:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_RIE_POS,
				DMA_CH_IER_RIE_LEN, 1);
		break;
	case XLGMAC_INT_DMA_CH_SR_RBU:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_RBUE_POS,
				DMA_CH_IER_RBUE_LEN, 1);
		break;
	case XLGMAC_INT_DMA_CH_SR_RPS:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_RSE_POS,
				DMA_CH_IER_RSE_LEN, 1);
		break;
	case XLGMAC_INT_DMA_CH_SR_TI_RI:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_TIE_POS,
				DMA_CH_IER_TIE_LEN, 1);
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_RIE_POS,
				DMA_CH_IER_RIE_LEN, 1);
		break;
	case XLGMAC_INT_DMA_CH_SR_FBE:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_FBEE_POS,
				DMA_CH_IER_FBEE_LEN, 1);
		break;
	case XLGMAC_INT_DMA_ALL:
		dma_ch_ier |= channel->saved_ier;
		break;
	default:
		return -1;
	}

	writel(dma_ch_ier, XLGMAC_DMA_REG(channel, DMA_CH_IER));

	return 0;
}