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
struct snd_soc_component {int dummy; } ;
struct cs35l35_private {int slave_mode; int i2s_mode; int pdm_mode; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS35L35_CLK_CTL1 ; 
 int /*<<< orphan*/  CS35L35_MS_MASK ; 
 int CS35L35_MS_SHIFT ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 131 
#define  SND_SOC_DAIFMT_CBS_CFS 130 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_PDM 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cs35l35_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs35l35_set_dai_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	struct cs35l35_private *cs35l35 = snd_soc_component_get_drvdata(component);

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		regmap_update_bits(cs35l35->regmap, CS35L35_CLK_CTL1,
				    CS35L35_MS_MASK, 1 << CS35L35_MS_SHIFT);
		cs35l35->slave_mode = false;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		regmap_update_bits(cs35l35->regmap, CS35L35_CLK_CTL1,
				    CS35L35_MS_MASK, 0 << CS35L35_MS_SHIFT);
		cs35l35->slave_mode = true;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		cs35l35->i2s_mode = true;
		cs35l35->pdm_mode = false;
		break;
	case SND_SOC_DAIFMT_PDM:
		cs35l35->pdm_mode = true;
		cs35l35->i2s_mode = false;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}