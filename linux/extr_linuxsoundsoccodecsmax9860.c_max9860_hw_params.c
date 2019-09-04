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
typedef  int u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct max9860_priv {int fmt; int pclk_rate; int psclk; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST_ULL (unsigned long long,int) ; 
 int EINVAL ; 
 int MAX9860_16KHZ ; 
 int MAX9860_ABCI ; 
 int MAX9860_ADLY ; 
 int /*<<< orphan*/  MAX9860_AUDIOCLKHIGH ; 
 int /*<<< orphan*/  MAX9860_AUDIOCLKLOW ; 
 int MAX9860_BSEL_48X ; 
 int MAX9860_BSEL_64X ; 
 int MAX9860_DBCI ; 
 int MAX9860_DDLY ; 
 int MAX9860_FREQ_12MHZ ; 
 int MAX9860_FREQ_13MHZ ; 
 int MAX9860_FREQ_19_2MHZ ; 
 int MAX9860_HIZ ; 
 int /*<<< orphan*/  MAX9860_IFC1A ; 
 int /*<<< orphan*/  MAX9860_IFC1B ; 
 int MAX9860_MASTER ; 
 int /*<<< orphan*/  MAX9860_PLL ; 
 int MAX9860_ST ; 
 int /*<<< orphan*/  MAX9860_SYSCLK ; 
 int MAX9860_TDM ; 
 int MAX9860_WCI ; 
#define  SND_SOC_DAIFMT_CBM_CFM 137 
#define  SND_SOC_DAIFMT_CBS_CFS 136 
#define  SND_SOC_DAIFMT_DSP_A 135 
#define  SND_SOC_DAIFMT_DSP_B 134 
 int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 133 
#define  SND_SOC_DAIFMT_IB_IF 132 
#define  SND_SOC_DAIFMT_IB_NF 131 
 int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 130 
 int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 struct max9860_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max9860_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct max9860_priv *max9860 = snd_soc_component_get_drvdata(component);
	u8 master;
	u8 ifc1a = 0;
	u8 ifc1b = 0;
	u8 sysclk = 0;
	unsigned long n;
	int ret;

	dev_dbg(component->dev, "hw_params %u Hz, %u channels\n",
		params_rate(params),
		params_channels(params));

	if (params_channels(params) == 2)
		ifc1b |= MAX9860_ST;

	switch (max9860->fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		master = 0;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		master = MAX9860_MASTER;
		break;
	default:
		return -EINVAL;
	}
	ifc1a |= master;

	if (master) {
		if (params_width(params) * params_channels(params) > 48)
			ifc1b |= MAX9860_BSEL_64X;
		else
			ifc1b |= MAX9860_BSEL_48X;
	}

	switch (max9860->fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		ifc1a |= MAX9860_DDLY;
		ifc1b |= MAX9860_ADLY;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		ifc1a |= MAX9860_WCI;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		if (params_width(params) != 16) {
			dev_err(component->dev,
				"DSP_A works for 16 bits per sample only.\n");
			return -EINVAL;
		}
		ifc1a |= MAX9860_DDLY | MAX9860_WCI | MAX9860_HIZ | MAX9860_TDM;
		ifc1b |= MAX9860_ADLY;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		if (params_width(params) != 16) {
			dev_err(component->dev,
				"DSP_B works for 16 bits per sample only.\n");
			return -EINVAL;
		}
		ifc1a |= MAX9860_WCI | MAX9860_HIZ | MAX9860_TDM;
		break;
	default:
		return -EINVAL;
	}

	switch (max9860->fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_NB_IF:
		switch (max9860->fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
		case SND_SOC_DAIFMT_DSP_A:
		case SND_SOC_DAIFMT_DSP_B:
			return -EINVAL;
		}
		ifc1a ^= MAX9860_WCI;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		switch (max9860->fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
		case SND_SOC_DAIFMT_DSP_A:
		case SND_SOC_DAIFMT_DSP_B:
			return -EINVAL;
		}
		ifc1a ^= MAX9860_WCI;
		/* fall through */
	case SND_SOC_DAIFMT_IB_NF:
		ifc1a ^= MAX9860_DBCI;
		ifc1b ^= MAX9860_ABCI;
		break;
	default:
		return -EINVAL;
	}

	dev_dbg(component->dev, "IFC1A  %02x\n", ifc1a);
	ret = regmap_write(max9860->regmap, MAX9860_IFC1A, ifc1a);
	if (ret) {
		dev_err(component->dev, "Failed to set IFC1A: %d\n", ret);
		return ret;
	}
	dev_dbg(component->dev, "IFC1B  %02x\n", ifc1b);
	ret = regmap_write(max9860->regmap, MAX9860_IFC1B, ifc1b);
	if (ret) {
		dev_err(component->dev, "Failed to set IFC1B: %d\n", ret);
		return ret;
	}

	/*
	 * Check if Integer Clock Mode is possible, but avoid it in slave mode
	 * since we then do not know if lrclk is derived from pclk and the
	 * datasheet mentions that the frequencies have to match exactly in
	 * order for this to work.
	 */
	if (params_rate(params) == 8000 || params_rate(params) == 16000) {
		if (master) {
			switch (max9860->pclk_rate) {
			case 12000000:
				sysclk = MAX9860_FREQ_12MHZ;
				break;
			case 13000000:
				sysclk = MAX9860_FREQ_13MHZ;
				break;
			case 19200000:
				sysclk = MAX9860_FREQ_19_2MHZ;
				break;
			default:
				/*
				 * Integer Clock Mode not possible. Leave
				 * sysclk at zero and fall through to the
				 * code below for PLL mode.
				 */
				break;
			}

			if (sysclk && params_rate(params) == 16000)
				sysclk |= MAX9860_16KHZ;
		}
	}

	/*
	 * Largest possible n:
	 *    65536 * 96 * 48kHz / 10MHz -> 30199
	 * Smallest possible n:
	 *    65536 * 96 *  8kHz / 20MHz -> 2517
	 * Both fit nicely in the available 15 bits, no need to apply any mask.
	 */
	n = DIV_ROUND_CLOSEST_ULL(65536ULL * 96 * params_rate(params),
				  max9860->pclk_rate);

	if (!sysclk) {
		/* PLL mode */
		if (params_rate(params) > 24000)
			sysclk |= MAX9860_16KHZ;

		if (!master)
			n |= 1; /* trigger rapid pll lock mode */
	}

	sysclk |= max9860->psclk;
	dev_dbg(component->dev, "SYSCLK %02x\n", sysclk);
	ret = regmap_write(max9860->regmap,
			   MAX9860_SYSCLK, sysclk);
	if (ret) {
		dev_err(component->dev, "Failed to set SYSCLK: %d\n", ret);
		return ret;
	}
	dev_dbg(component->dev, "N %lu\n", n);
	ret = regmap_write(max9860->regmap,
			   MAX9860_AUDIOCLKHIGH, n >> 8);
	if (ret) {
		dev_err(component->dev, "Failed to set NHI: %d\n", ret);
		return ret;
	}
	ret = regmap_write(max9860->regmap,
			   MAX9860_AUDIOCLKLOW, n & 0xff);
	if (ret) {
		dev_err(component->dev, "Failed to set NLO: %d\n", ret);
		return ret;
	}

	if (!master) {
		dev_dbg(component->dev, "Enable PLL\n");
		ret = regmap_update_bits(max9860->regmap, MAX9860_AUDIOCLKHIGH,
					 MAX9860_PLL, MAX9860_PLL);
		if (ret) {
			dev_err(component->dev, "Failed to enable PLL: %d\n",
				ret);
			return ret;
		}
	}

	return 0;
}