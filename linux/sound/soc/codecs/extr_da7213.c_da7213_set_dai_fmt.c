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
struct snd_soc_component {int dummy; } ;
struct da7213_priv {int master; } ;

/* Variables and functions */
 int DA7213_DAI_BCLKS_PER_WCLK_64 ; 
 int DA7213_DAI_BCLKS_PER_WCLK_MASK ; 
 int /*<<< orphan*/  DA7213_DAI_CLK_MODE ; 
 int DA7213_DAI_CLK_POL_INV ; 
 int DA7213_DAI_CLK_POL_MASK ; 
 int /*<<< orphan*/  DA7213_DAI_CTRL ; 
 int DA7213_DAI_FORMAT_DSP ; 
 int DA7213_DAI_FORMAT_I2S_MODE ; 
 int DA7213_DAI_FORMAT_LEFT_J ; 
 int DA7213_DAI_FORMAT_MASK ; 
 int DA7213_DAI_FORMAT_RIGHT_J ; 
 int /*<<< orphan*/  DA7213_DAI_OFFSET ; 
 int DA7213_DAI_WCLK_POL_INV ; 
 int DA7213_DAI_WCLK_POL_MASK ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 138 
#define  SND_SOC_DAIFMT_CBS_CFS 137 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 136 
#define  SND_SOC_DAIFMT_IB_IF 135 
#define  SND_SOC_DAIFMT_IB_NF 134 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 133 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 132 
#define  SND_SOC_DAIFMT_NB_NF 131 
#define  SND_SOC_DAIFMT_RIGHT_J 130 
#define  SND_SOC_DAI_FORMAT_DSP_A 129 
#define  SND_SOC_DAI_FORMAT_DSP_B 128 
 struct da7213_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int da7213_set_dai_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	struct da7213_priv *da7213 = snd_soc_component_get_drvdata(component);
	u8 dai_clk_mode = 0, dai_ctrl = 0;
	u8 dai_offset = 0;

	/* Set master/slave mode */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		da7213->master = true;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		da7213->master = false;
		break;
	default:
		return -EINVAL;
	}

	/* Set clock normal/inverted */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_LEFT_J:
	case SND_SOC_DAIFMT_RIGHT_J:
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			break;
		case SND_SOC_DAIFMT_NB_IF:
			dai_clk_mode |= DA7213_DAI_WCLK_POL_INV;
			break;
		case SND_SOC_DAIFMT_IB_NF:
			dai_clk_mode |= DA7213_DAI_CLK_POL_INV;
			break;
		case SND_SOC_DAIFMT_IB_IF:
			dai_clk_mode |= DA7213_DAI_WCLK_POL_INV |
					DA7213_DAI_CLK_POL_INV;
			break;
		default:
			return -EINVAL;
		}
		break;
	case SND_SOC_DAI_FORMAT_DSP_A:
	case SND_SOC_DAI_FORMAT_DSP_B:
		/* The bclk is inverted wrt ASoC conventions */
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			dai_clk_mode |= DA7213_DAI_CLK_POL_INV;
			break;
		case SND_SOC_DAIFMT_NB_IF:
			dai_clk_mode |= DA7213_DAI_WCLK_POL_INV |
					DA7213_DAI_CLK_POL_INV;
			break;
		case SND_SOC_DAIFMT_IB_NF:
			break;
		case SND_SOC_DAIFMT_IB_IF:
			dai_clk_mode |= DA7213_DAI_WCLK_POL_INV;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	/* Only I2S is supported */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		dai_ctrl |= DA7213_DAI_FORMAT_I2S_MODE;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		dai_ctrl |= DA7213_DAI_FORMAT_LEFT_J;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		dai_ctrl |= DA7213_DAI_FORMAT_RIGHT_J;
		break;
	case SND_SOC_DAI_FORMAT_DSP_A: /* L data MSB after FRM LRC */
		dai_ctrl |= DA7213_DAI_FORMAT_DSP;
		dai_offset = 1;
		break;
	case SND_SOC_DAI_FORMAT_DSP_B: /* L data MSB during FRM LRC */
		dai_ctrl |= DA7213_DAI_FORMAT_DSP;
		break;
	default:
		return -EINVAL;
	}

	/* By default only 64 BCLK per WCLK is supported */
	dai_clk_mode |= DA7213_DAI_BCLKS_PER_WCLK_64;

	snd_soc_component_update_bits(component, DA7213_DAI_CLK_MODE,
			    DA7213_DAI_BCLKS_PER_WCLK_MASK |
			    DA7213_DAI_CLK_POL_MASK | DA7213_DAI_WCLK_POL_MASK,
			    dai_clk_mode);
	snd_soc_component_update_bits(component, DA7213_DAI_CTRL, DA7213_DAI_FORMAT_MASK,
			    dai_ctrl);
	snd_soc_component_write(component, DA7213_DAI_OFFSET, dai_offset);

	return 0;
}