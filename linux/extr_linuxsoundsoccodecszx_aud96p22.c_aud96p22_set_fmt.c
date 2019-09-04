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
struct snd_soc_dai {int /*<<< orphan*/  component; } ;
struct regmap {int dummy; } ;
struct aud96p22_priv {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD96P22_I2S1_CONFIG_0 ; 
 int EINVAL ; 
 unsigned int I2S1_MODE_I2S ; 
 unsigned int I2S1_MODE_LEFT_J ; 
 unsigned int I2S1_MODE_MASK ; 
 unsigned int I2S1_MODE_RIGHT_J ; 
 unsigned int I2S1_MS_MODE ; 
#define  SND_SOC_DAIFMT_CBM_CFM 132 
#define  SND_SOC_DAIFMT_CBS_CFS 131 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct aud96p22_priv* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aud96p22_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct aud96p22_priv *priv = snd_soc_component_get_drvdata(dai->component);
	struct regmap *regmap = priv->regmap;
	unsigned int val;

	/* Master/slave mode */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		val = 0;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		val = I2S1_MS_MODE;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(regmap, AUD96P22_I2S1_CONFIG_0, I2S1_MS_MODE, val);

	/* Audio format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_RIGHT_J:
		val = I2S1_MODE_RIGHT_J;
		break;
	case SND_SOC_DAIFMT_I2S:
		val = I2S1_MODE_I2S;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		val = I2S1_MODE_LEFT_J;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(regmap, AUD96P22_I2S1_CONFIG_0, I2S1_MODE_MASK, val);

	return 0;
}