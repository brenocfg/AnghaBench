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
struct ssm2518 {int right_j; int /*<<< orphan*/  regmap; } ;
struct snd_soc_dai {int /*<<< orphan*/  component; } ;

/* Variables and functions */
 int EINVAL ; 
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
 int /*<<< orphan*/  SSM2518_REG_SAI_CTRL1 ; 
 int /*<<< orphan*/  SSM2518_REG_SAI_CTRL2 ; 
 unsigned int SSM2518_SAI_CTRL1_FMT_I2S ; 
 unsigned int SSM2518_SAI_CTRL1_FMT_LJ ; 
 unsigned int SSM2518_SAI_CTRL1_FMT_RJ_24BIT ; 
 unsigned int SSM2518_SAI_CTRL2_BCLK_INVERT ; 
 unsigned int SSM2518_SAI_CTRL2_LRCLK_INVERT ; 
 unsigned int SSM2518_SAI_CTRL2_LRCLK_PULSE ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct ssm2518* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssm2518_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct ssm2518 *ssm2518 = snd_soc_component_get_drvdata(dai->component);
	unsigned int ctrl1 = 0, ctrl2 = 0;
	bool invert_fclk;
	int ret;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		invert_fclk = false;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		ctrl2 |= SSM2518_SAI_CTRL2_BCLK_INVERT;
		invert_fclk = false;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		invert_fclk = true;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		ctrl2 |= SSM2518_SAI_CTRL2_BCLK_INVERT;
		invert_fclk = true;
		break;
	default:
		return -EINVAL;
	}

	ssm2518->right_j = false;
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		ctrl1 |= SSM2518_SAI_CTRL1_FMT_I2S;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		ctrl1 |= SSM2518_SAI_CTRL1_FMT_LJ;
		invert_fclk = !invert_fclk;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		ctrl1 |= SSM2518_SAI_CTRL1_FMT_RJ_24BIT;
		ssm2518->right_j = true;
		invert_fclk = !invert_fclk;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		ctrl2 |= SSM2518_SAI_CTRL2_LRCLK_PULSE;
		ctrl1 |= SSM2518_SAI_CTRL1_FMT_I2S;
		invert_fclk = false;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		ctrl2 |= SSM2518_SAI_CTRL2_LRCLK_PULSE;
		ctrl1 |= SSM2518_SAI_CTRL1_FMT_LJ;
		invert_fclk = false;
		break;
	default:
		return -EINVAL;
	}

	if (invert_fclk)
		ctrl2 |= SSM2518_SAI_CTRL2_LRCLK_INVERT;

	ret = regmap_write(ssm2518->regmap, SSM2518_REG_SAI_CTRL1, ctrl1);
	if (ret)
		return ret;

	return regmap_write(ssm2518->regmap, SSM2518_REG_SAI_CTRL2, ctrl2);
}