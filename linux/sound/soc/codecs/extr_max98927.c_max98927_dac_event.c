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
struct max98927_priv {int tdm_mode; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX98927_AMP_EN_MASK ; 
 int /*<<< orphan*/  MAX98927_GLOBAL_EN_MASK ; 
 int /*<<< orphan*/  MAX98927_R003A_AMP_EN ; 
 int /*<<< orphan*/  MAX98927_R00FF_GLOBAL_SHDN ; 
#define  SND_SOC_DAPM_POST_PMD 130 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct max98927_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max98927_dac_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct max98927_priv *max98927 = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		max98927->tdm_mode = false;
		break;
	case SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(max98927->regmap,
			MAX98927_R003A_AMP_EN,
			MAX98927_AMP_EN_MASK, 1);
		regmap_update_bits(max98927->regmap,
			MAX98927_R00FF_GLOBAL_SHDN,
			MAX98927_GLOBAL_EN_MASK, 1);
		break;
	case SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(max98927->regmap,
			MAX98927_R00FF_GLOBAL_SHDN,
			MAX98927_GLOBAL_EN_MASK, 0);
		regmap_update_bits(max98927->regmap,
			MAX98927_R003A_AMP_EN,
			MAX98927_AMP_EN_MASK, 0);
		break;
	default:
		return 0;
	}
	return 0;
}