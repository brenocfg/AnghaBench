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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct cs35l33_private {int is_tdm_mode; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS35L33_ADSP_CTL ; 
 int /*<<< orphan*/  CS35L33_MS_MASK ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 131 
#define  SND_SOC_DAIFMT_CBS_CFS 130 
#define  SND_SOC_DAIFMT_DSP_A 129 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 128 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs35l33_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs35l33_set_dai_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	struct cs35l33_private *priv = snd_soc_component_get_drvdata(component);

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		regmap_update_bits(priv->regmap, CS35L33_ADSP_CTL,
			CS35L33_MS_MASK, CS35L33_MS_MASK);
		dev_dbg(component->dev, "Audio port in master mode\n");
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		regmap_update_bits(priv->regmap, CS35L33_ADSP_CTL,
			CS35L33_MS_MASK, 0);
		dev_dbg(component->dev, "Audio port in slave mode\n");
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		/*
		 * tdm mode in cs35l33 resembles dsp-a mode very
		 * closely, it is dsp-a with fsync shifted left by half bclk
		 */
		priv->is_tdm_mode = true;
		dev_dbg(component->dev, "Audio port in TDM mode\n");
		break;
	case SND_SOC_DAIFMT_I2S:
		priv->is_tdm_mode = false;
		dev_dbg(component->dev, "Audio port in I2S mode\n");
		break;
	default:
		return -EINVAL;
	}

	return 0;
}