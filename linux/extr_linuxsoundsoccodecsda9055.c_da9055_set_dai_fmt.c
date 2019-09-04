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
typedef  scalar_t__ u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct da9055_priv {scalar_t__ master; } ;

/* Variables and functions */
 scalar_t__ DA9055_AIF_BCLKS_PER_WCLK_32 ; 
 int DA9055_AIF_BCLK_MASK ; 
 scalar_t__ DA9055_AIF_CLK_EN_MASTER_MODE ; 
 scalar_t__ DA9055_AIF_CLK_EN_SLAVE_MODE ; 
 int /*<<< orphan*/  DA9055_AIF_CLK_MODE ; 
 int DA9055_AIF_CLK_MODE_MASK ; 
 int /*<<< orphan*/  DA9055_AIF_CTRL ; 
 scalar_t__ DA9055_AIF_FORMAT_DSP ; 
 scalar_t__ DA9055_AIF_FORMAT_I2S_MODE ; 
 scalar_t__ DA9055_AIF_FORMAT_LEFT_J ; 
 int DA9055_AIF_FORMAT_MASK ; 
 scalar_t__ DA9055_AIF_FORMAT_RIGHT_J ; 
 int /*<<< orphan*/  DA9055_PLL_CTRL ; 
 int DA9055_PLL_EN ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 133 
#define  SND_SOC_DAIFMT_CBS_CFS 132 
#define  SND_SOC_DAIFMT_DSP_A 131 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 struct da9055_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static int da9055_set_dai_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	struct da9055_priv *da9055 = snd_soc_component_get_drvdata(component);
	u8 aif_clk_mode, aif_ctrl, mode;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		/* DA9055 in I2S Master Mode */
		mode = 1;
		aif_clk_mode = DA9055_AIF_CLK_EN_MASTER_MODE;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		/* DA9055 in I2S Slave Mode */
		mode = 0;
		aif_clk_mode = DA9055_AIF_CLK_EN_SLAVE_MODE;
		break;
	default:
		return -EINVAL;
	}

	/* Don't allow change of mode if PLL is enabled */
	if ((snd_soc_component_read32(component, DA9055_PLL_CTRL) & DA9055_PLL_EN) &&
	    (da9055->master != mode))
		return -EINVAL;

	da9055->master = mode;

	/* Only I2S is supported */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		aif_ctrl = DA9055_AIF_FORMAT_I2S_MODE;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		aif_ctrl = DA9055_AIF_FORMAT_LEFT_J;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		aif_ctrl = DA9055_AIF_FORMAT_RIGHT_J;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		aif_ctrl = DA9055_AIF_FORMAT_DSP;
		break;
	default:
		return -EINVAL;
	}

	/* By default only 32 BCLK per WCLK is supported */
	aif_clk_mode |= DA9055_AIF_BCLKS_PER_WCLK_32;

	snd_soc_component_update_bits(component, DA9055_AIF_CLK_MODE,
			    (DA9055_AIF_CLK_MODE_MASK | DA9055_AIF_BCLK_MASK),
			    aif_clk_mode);
	snd_soc_component_update_bits(component, DA9055_AIF_CTRL, DA9055_AIF_FORMAT_MASK,
			    aif_ctrl);
	return 0;
}