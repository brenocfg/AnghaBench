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
typedef  int u32 ;
struct fsl_ssi {unsigned int dai_fmt; int i2s_net; int /*<<< orphan*/  regs; scalar_t__ synchronous; int /*<<< orphan*/  dev; int /*<<< orphan*/  baudclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SSI_SCR ; 
 int /*<<< orphan*/  REG_SSI_SRCCR ; 
 int /*<<< orphan*/  REG_SSI_SRCR ; 
 int /*<<< orphan*/  REG_SSI_STCCR ; 
 int /*<<< orphan*/  REG_SSI_STCR ; 
#define  SND_SOC_DAIFMT_AC97 139 
#define  SND_SOC_DAIFMT_CBM_CFM 138 
#define  SND_SOC_DAIFMT_CBM_CFS 137 
#define  SND_SOC_DAIFMT_CBS_CFS 136 
#define  SND_SOC_DAIFMT_DSP_A 135 
#define  SND_SOC_DAIFMT_DSP_B 134 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 133 
#define  SND_SOC_DAIFMT_IB_IF 132 
#define  SND_SOC_DAIFMT_IB_NF 131 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 130 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int SSI_SCR_I2S_MODE_MASK ; 
 int SSI_SCR_I2S_MODE_MASTER ; 
 int SSI_SCR_I2S_MODE_SLAVE ; 
 int SSI_SCR_NET ; 
 int SSI_SCR_SYN ; 
 int SSI_SCR_SYNC_TX_FS ; 
 int SSI_SCR_SYS_CLK_EN ; 
 int SSI_SRCR_RXDIR ; 
 int SSI_STCR_TEFS ; 
 int SSI_STCR_TFDIR ; 
 int SSI_STCR_TFSI ; 
 int SSI_STCR_TFSL ; 
 int SSI_STCR_TSCKP ; 
 int SSI_STCR_TXBIT0 ; 
 int SSI_STCR_TXDIR ; 
 int SSI_SxCCR_DC (int) ; 
 int SSI_SxCCR_DC_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fsl_ssi_is_ac97 (struct fsl_ssi*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int _fsl_ssi_set_dai_fmt(struct fsl_ssi *ssi, unsigned int fmt)
{
	u32 strcr = 0, scr = 0, stcr, srcr, mask;

	ssi->dai_fmt = fmt;

	/* Synchronize frame sync clock for TE to avoid data slipping */
	scr |= SSI_SCR_SYNC_TX_FS;

	/* Set to default shifting settings: LSB_ALIGNED */
	strcr |= SSI_STCR_TXBIT0;

	/* Use Network mode as default */
	ssi->i2s_net = SSI_SCR_NET;
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
		case SND_SOC_DAIFMT_CBS_CFS:
			if (IS_ERR(ssi->baudclk)) {
				dev_err(ssi->dev,
					"missing baudclk for master mode\n");
				return -EINVAL;
			}
			/* fall through */
		case SND_SOC_DAIFMT_CBM_CFS:
			ssi->i2s_net |= SSI_SCR_I2S_MODE_MASTER;
			break;
		case SND_SOC_DAIFMT_CBM_CFM:
			ssi->i2s_net |= SSI_SCR_I2S_MODE_SLAVE;
			break;
		default:
			return -EINVAL;
		}

		regmap_update_bits(ssi->regs, REG_SSI_STCCR,
				   SSI_SxCCR_DC_MASK, SSI_SxCCR_DC(2));
		regmap_update_bits(ssi->regs, REG_SSI_SRCCR,
				   SSI_SxCCR_DC_MASK, SSI_SxCCR_DC(2));

		/* Data on rising edge of bclk, frame low, 1clk before data */
		strcr |= SSI_STCR_TFSI | SSI_STCR_TSCKP | SSI_STCR_TEFS;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		/* Data on rising edge of bclk, frame high */
		strcr |= SSI_STCR_TSCKP;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		/* Data on rising edge of bclk, frame high, 1clk before data */
		strcr |= SSI_STCR_TFSL | SSI_STCR_TSCKP | SSI_STCR_TEFS;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		/* Data on rising edge of bclk, frame high */
		strcr |= SSI_STCR_TFSL | SSI_STCR_TSCKP;
		break;
	case SND_SOC_DAIFMT_AC97:
		/* Data on falling edge of bclk, frame high, 1clk before data */
		strcr |= SSI_STCR_TEFS;
		break;
	default:
		return -EINVAL;
	}

	scr |= ssi->i2s_net;

	/* DAI clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		/* Nothing to do for both normal cases */
		break;
	case SND_SOC_DAIFMT_IB_NF:
		/* Invert bit clock */
		strcr ^= SSI_STCR_TSCKP;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		/* Invert frame clock */
		strcr ^= SSI_STCR_TFSI;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		/* Invert both clocks */
		strcr ^= SSI_STCR_TSCKP;
		strcr ^= SSI_STCR_TFSI;
		break;
	default:
		return -EINVAL;
	}

	/* DAI clock master masks */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		/* Output bit and frame sync clocks */
		strcr |= SSI_STCR_TFDIR | SSI_STCR_TXDIR;
		scr |= SSI_SCR_SYS_CLK_EN;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		/* Input bit or frame sync clocks */
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		/* Input bit clock but output frame sync clock */
		strcr |= SSI_STCR_TFDIR;
		break;
	default:
		return -EINVAL;
	}

	stcr = strcr;
	srcr = strcr;

	/* Set SYN mode and clear RXDIR bit when using SYN or AC97 mode */
	if (ssi->synchronous || fsl_ssi_is_ac97(ssi)) {
		srcr &= ~SSI_SRCR_RXDIR;
		scr |= SSI_SCR_SYN;
	}

	mask = SSI_STCR_TFDIR | SSI_STCR_TXDIR | SSI_STCR_TSCKP |
	       SSI_STCR_TFSL | SSI_STCR_TFSI | SSI_STCR_TEFS | SSI_STCR_TXBIT0;

	regmap_update_bits(ssi->regs, REG_SSI_STCR, mask, stcr);
	regmap_update_bits(ssi->regs, REG_SSI_SRCR, mask, srcr);

	mask = SSI_SCR_SYNC_TX_FS | SSI_SCR_I2S_MODE_MASK |
	       SSI_SCR_SYS_CLK_EN | SSI_SCR_SYN;
	regmap_update_bits(ssi->regs, REG_SSI_SCR, mask, scr);

	return 0;
}