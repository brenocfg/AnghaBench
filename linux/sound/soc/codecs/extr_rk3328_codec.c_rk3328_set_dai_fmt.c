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
struct rk3328_codec_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int DAC_I2S_MODE_MASK ; 
 unsigned int DAC_I2S_MODE_MASTER ; 
 unsigned int DAC_I2S_MODE_SLAVE ; 
 int /*<<< orphan*/  DAC_INIT_CTRL1 ; 
 int /*<<< orphan*/  DAC_INIT_CTRL2 ; 
 unsigned int DAC_MODE_I2S ; 
 unsigned int DAC_MODE_LJM ; 
 int DAC_MODE_MASK ; 
 unsigned int DAC_MODE_PCM ; 
 unsigned int DAC_MODE_RJM ; 
 int EINVAL ; 
 unsigned int PIN_DIRECTION_IN ; 
 int PIN_DIRECTION_MASK ; 
 unsigned int PIN_DIRECTION_OUT ; 
#define  SND_SOC_DAIFMT_CBM_CFM 134 
#define  SND_SOC_DAIFMT_CBS_CFS 133 
#define  SND_SOC_DAIFMT_DSP_A 132 
#define  SND_SOC_DAIFMT_DSP_B 131 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 struct rk3328_codec_priv* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk3328_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct rk3328_codec_priv *rk3328 =
		snd_soc_component_get_drvdata(dai->component);
	unsigned int val;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		val = PIN_DIRECTION_IN | DAC_I2S_MODE_SLAVE;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		val = PIN_DIRECTION_OUT | DAC_I2S_MODE_MASTER;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(rk3328->regmap, DAC_INIT_CTRL1,
			   PIN_DIRECTION_MASK | DAC_I2S_MODE_MASK, val);

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		val = DAC_MODE_PCM;
		break;
	case SND_SOC_DAIFMT_I2S:
		val = DAC_MODE_I2S;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		val = DAC_MODE_RJM;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		val = DAC_MODE_LJM;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(rk3328->regmap, DAC_INIT_CTRL2,
			   DAC_MODE_MASK, val);

	return 0;
}