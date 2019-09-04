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
struct snd_soc_dai {int dummy; } ;
struct fsl_esai {int slave_mode; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESAI_xCCR_xCKD ; 
 int ESAI_xCCR_xCKP ; 
 int ESAI_xCCR_xFSD ; 
 int ESAI_xCCR_xFSP ; 
 int ESAI_xCCR_xHCKP ; 
 int ESAI_xCR_xFSL ; 
 int ESAI_xCR_xFSR ; 
 int ESAI_xCR_xWA ; 
 int /*<<< orphan*/  REG_ESAI_RCCR ; 
 int /*<<< orphan*/  REG_ESAI_RCR ; 
 int /*<<< orphan*/  REG_ESAI_TCCR ; 
 int /*<<< orphan*/  REG_ESAI_TCR ; 
#define  SND_SOC_DAIFMT_CBM_CFM 140 
#define  SND_SOC_DAIFMT_CBM_CFS 139 
#define  SND_SOC_DAIFMT_CBS_CFM 138 
#define  SND_SOC_DAIFMT_CBS_CFS 137 
#define  SND_SOC_DAIFMT_DSP_A 136 
#define  SND_SOC_DAIFMT_DSP_B 135 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 134 
#define  SND_SOC_DAIFMT_IB_IF 133 
#define  SND_SOC_DAIFMT_IB_NF 132 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 131 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 130 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct fsl_esai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_esai_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);
	u32 xcr = 0, xccr = 0, mask;

	/* DAI mode */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		/* Data on rising edge of bclk, frame low, 1clk before data */
		xcr |= ESAI_xCR_xFSR;
		xccr |= ESAI_xCCR_xFSP | ESAI_xCCR_xCKP | ESAI_xCCR_xHCKP;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		/* Data on rising edge of bclk, frame high */
		xccr |= ESAI_xCCR_xCKP | ESAI_xCCR_xHCKP;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		/* Data on rising edge of bclk, frame high, right aligned */
		xccr |= ESAI_xCCR_xCKP | ESAI_xCCR_xHCKP;
		xcr  |= ESAI_xCR_xWA;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		/* Data on rising edge of bclk, frame high, 1clk before data */
		xcr |= ESAI_xCR_xFSL | ESAI_xCR_xFSR;
		xccr |= ESAI_xCCR_xCKP | ESAI_xCCR_xHCKP;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		/* Data on rising edge of bclk, frame high */
		xcr |= ESAI_xCR_xFSL;
		xccr |= ESAI_xCCR_xCKP | ESAI_xCCR_xHCKP;
		break;
	default:
		return -EINVAL;
	}

	/* DAI clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		/* Nothing to do for both normal cases */
		break;
	case SND_SOC_DAIFMT_IB_NF:
		/* Invert bit clock */
		xccr ^= ESAI_xCCR_xCKP | ESAI_xCCR_xHCKP;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		/* Invert frame clock */
		xccr ^= ESAI_xCCR_xFSP;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		/* Invert both clocks */
		xccr ^= ESAI_xCCR_xCKP | ESAI_xCCR_xHCKP | ESAI_xCCR_xFSP;
		break;
	default:
		return -EINVAL;
	}

	esai_priv->slave_mode = false;

	/* DAI clock master masks */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		esai_priv->slave_mode = true;
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		xccr |= ESAI_xCCR_xCKD;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		xccr |= ESAI_xCCR_xFSD;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		xccr |= ESAI_xCCR_xFSD | ESAI_xCCR_xCKD;
		break;
	default:
		return -EINVAL;
	}

	mask = ESAI_xCR_xFSL | ESAI_xCR_xFSR | ESAI_xCR_xWA;
	regmap_update_bits(esai_priv->regmap, REG_ESAI_TCR, mask, xcr);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_RCR, mask, xcr);

	mask = ESAI_xCCR_xCKP | ESAI_xCCR_xHCKP | ESAI_xCCR_xFSP |
		ESAI_xCCR_xFSD | ESAI_xCCR_xCKD;
	regmap_update_bits(esai_priv->regmap, REG_ESAI_TCCR, mask, xccr);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_RCCR, mask, xccr);

	return 0;
}