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
struct tas571x_private {int format; int /*<<< orphan*/  regmap; } ;
struct snd_soc_dai {int /*<<< orphan*/  component; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  TAS571X_SDI_FMT_MASK ; 
 int /*<<< orphan*/  TAS571X_SDI_REG ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct tas571x_private* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tas571x_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct tas571x_private *priv = snd_soc_component_get_drvdata(dai->component);
	u32 val;

	switch (priv->format & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_RIGHT_J:
		val = 0x00;
		break;
	case SND_SOC_DAIFMT_I2S:
		val = 0x03;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		val = 0x06;
		break;
	default:
		return -EINVAL;
	}

	if (params_width(params) >= 24)
		val += 2;
	else if (params_width(params) >= 20)
		val += 1;

	return regmap_update_bits(priv->regmap, TAS571X_SDI_REG,
				  TAS571X_SDI_FMT_MASK, val);
}