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
struct snd_soc_dapm_widget {int shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct rt5677_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int RT5677_AD_MONOL_CLK_SEL_MASK ; 
 unsigned int RT5677_AD_MONOL_CLK_SEL_SFT ; 
 unsigned int RT5677_AD_MONOR_CLK_SEL_MASK ; 
 unsigned int RT5677_AD_MONOR_CLK_SEL_SFT ; 
 unsigned int RT5677_AD_STO1_CLK_SEL_MASK ; 
 unsigned int RT5677_AD_STO1_CLK_SEL_SFT ; 
 unsigned int RT5677_AD_STO2_CLK_SEL_MASK ; 
 unsigned int RT5677_AD_STO2_CLK_SEL_SFT ; 
 unsigned int RT5677_AD_STO3_CLK_SEL_MASK ; 
 unsigned int RT5677_AD_STO3_CLK_SEL_SFT ; 
 unsigned int RT5677_AD_STO4_CLK_SEL_MASK ; 
 unsigned int RT5677_AD_STO4_CLK_SEL_SFT ; 
 int /*<<< orphan*/  RT5677_ASRC_5 ; 
 int /*<<< orphan*/  RT5677_ASRC_6 ; 
 unsigned int RT5677_CLK_SEL_I2S1_ASRC ; 
 unsigned int RT5677_CLK_SEL_I2S6_ASRC ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct rt5677_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5677_dmic_use_asrc(struct snd_soc_dapm_widget *source,
			 struct snd_soc_dapm_widget *sink)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	struct rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	unsigned int asrc_setting;

	switch (source->shift) {
	case 11:
		regmap_read(rt5677->regmap, RT5677_ASRC_5, &asrc_setting);
		asrc_setting = (asrc_setting & RT5677_AD_STO1_CLK_SEL_MASK) >>
				RT5677_AD_STO1_CLK_SEL_SFT;
		break;

	case 10:
		regmap_read(rt5677->regmap, RT5677_ASRC_5, &asrc_setting);
		asrc_setting = (asrc_setting & RT5677_AD_STO2_CLK_SEL_MASK) >>
				RT5677_AD_STO2_CLK_SEL_SFT;
		break;

	case 9:
		regmap_read(rt5677->regmap, RT5677_ASRC_5, &asrc_setting);
		asrc_setting = (asrc_setting & RT5677_AD_STO3_CLK_SEL_MASK) >>
				RT5677_AD_STO3_CLK_SEL_SFT;
		break;

	case 8:
		regmap_read(rt5677->regmap, RT5677_ASRC_5, &asrc_setting);
		asrc_setting = (asrc_setting & RT5677_AD_STO4_CLK_SEL_MASK) >>
			RT5677_AD_STO4_CLK_SEL_SFT;
		break;

	case 7:
		regmap_read(rt5677->regmap, RT5677_ASRC_6, &asrc_setting);
		asrc_setting = (asrc_setting & RT5677_AD_MONOL_CLK_SEL_MASK) >>
			RT5677_AD_MONOL_CLK_SEL_SFT;
		break;

	case 6:
		regmap_read(rt5677->regmap, RT5677_ASRC_6, &asrc_setting);
		asrc_setting = (asrc_setting & RT5677_AD_MONOR_CLK_SEL_MASK) >>
			RT5677_AD_MONOR_CLK_SEL_SFT;
		break;

	default:
		return 0;
	}

	if (asrc_setting >= RT5677_CLK_SEL_I2S1_ASRC &&
	    asrc_setting <= RT5677_CLK_SEL_I2S6_ASRC)
		return 1;

	return 0;
}