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
struct sun8i_codec {int /*<<< orphan*/  regmap; } ;
struct snd_soc_dai {int /*<<< orphan*/  component; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 136 
#define  SND_SOC_DAIFMT_CBS_CFS 135 
#define  SND_SOC_DAIFMT_DSP_A 134 
#define  SND_SOC_DAIFMT_DSP_B 133 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 132 
#define  SND_SOC_DAIFMT_IB_IF 131 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 130 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  SUN8I_AIF1CLK_CTRL ; 
 int SUN8I_AIF1CLK_CTRL_AIF1_BCLK_INV ; 
 int SUN8I_AIF1CLK_CTRL_AIF1_DATA_FMT ; 
 int SUN8I_AIF1CLK_CTRL_AIF1_LRCK_INV ; 
 int SUN8I_AIF1CLK_CTRL_AIF1_MSTR_MOD ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sun8i_codec* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun8i_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct sun8i_codec *scodec = snd_soc_component_get_drvdata(dai->component);
	u32 value;

	/* clock masters */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS: /* Codec slave, DAI master */
		value = 0x1;
		break;
	case SND_SOC_DAIFMT_CBM_CFM: /* Codec Master, DAI slave */
		value = 0x0;
		break;
	default:
		return -EINVAL;
	}
	regmap_update_bits(scodec->regmap, SUN8I_AIF1CLK_CTRL,
			   BIT(SUN8I_AIF1CLK_CTRL_AIF1_MSTR_MOD),
			   value << SUN8I_AIF1CLK_CTRL_AIF1_MSTR_MOD);

	/* clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF: /* Normal */
		value = 0x0;
		break;
	case SND_SOC_DAIFMT_IB_IF: /* Inversion */
		value = 0x1;
		break;
	default:
		return -EINVAL;
	}
	regmap_update_bits(scodec->regmap, SUN8I_AIF1CLK_CTRL,
			   BIT(SUN8I_AIF1CLK_CTRL_AIF1_BCLK_INV),
			   value << SUN8I_AIF1CLK_CTRL_AIF1_BCLK_INV);

	/*
	 * It appears that the DAI and the codec don't share the same
	 * polarity for the LRCK signal when they mean 'normal' and
	 * 'inverted' in the datasheet.
	 *
	 * Since the DAI here is our regular i2s driver that have been
	 * tested with way more codecs than just this one, it means
	 * that the codec probably gets it backward, and we have to
	 * invert the value here.
	 */
	regmap_update_bits(scodec->regmap, SUN8I_AIF1CLK_CTRL,
			   BIT(SUN8I_AIF1CLK_CTRL_AIF1_LRCK_INV),
			   !value << SUN8I_AIF1CLK_CTRL_AIF1_LRCK_INV);

	/* DAI format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		value = 0x0;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		value = 0x1;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		value = 0x2;
		break;
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		value = 0x3;
		break;
	default:
		return -EINVAL;
	}
	regmap_update_bits(scodec->regmap, SUN8I_AIF1CLK_CTRL,
			   BIT(SUN8I_AIF1CLK_CTRL_AIF1_DATA_FMT),
			   value << SUN8I_AIF1CLK_CTRL_AIF1_DATA_FMT);

	return 0;
}