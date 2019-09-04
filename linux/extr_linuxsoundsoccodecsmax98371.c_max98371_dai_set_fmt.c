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
struct max98371_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int MAX98371_DAI_LEFT ; 
 unsigned int MAX98371_DAI_RIGHT ; 
 int /*<<< orphan*/  MAX98371_FMT ; 
 int /*<<< orphan*/  MAX98371_FMT_MODE_MASK ; 
#define  SND_SOC_DAIFMT_CBS_CFS 131 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct max98371_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max98371_dai_set_fmt(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	struct max98371_priv *max98371 = snd_soc_component_get_drvdata(component);
	unsigned int val = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	default:
		dev_err(component->dev, "DAI clock mode unsupported");
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		val |= 0;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		val |= MAX98371_DAI_RIGHT;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		val |= MAX98371_DAI_LEFT;
		break;
	default:
		dev_err(component->dev, "DAI wrong mode unsupported");
		return -EINVAL;
	}
	regmap_update_bits(max98371->regmap, MAX98371_FMT,
			MAX98371_FMT_MODE_MASK, val);
	return 0;
}