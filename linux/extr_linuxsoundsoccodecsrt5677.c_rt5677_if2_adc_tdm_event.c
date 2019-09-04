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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct rt5677_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int RT5677_IF2_ADC_CTRL_MASK ; 
 int /*<<< orphan*/  RT5677_IF2_ADC_MODE_MASK ; 
 int /*<<< orphan*/  RT5677_IF2_ADC_MODE_TDM ; 
 int /*<<< orphan*/  RT5677_TDM2_CTRL1 ; 
 int /*<<< orphan*/  RT5677_TDM2_CTRL2 ; 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rt5677_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5677_if2_adc_tdm_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	unsigned int value;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		regmap_read(rt5677->regmap, RT5677_TDM2_CTRL2, &value);
		if (value & RT5677_IF2_ADC_CTRL_MASK)
			regmap_update_bits(rt5677->regmap, RT5677_TDM2_CTRL1,
				RT5677_IF2_ADC_MODE_MASK,
				RT5677_IF2_ADC_MODE_TDM);
		break;

	default:
		return 0;
	}

	return 0;
}