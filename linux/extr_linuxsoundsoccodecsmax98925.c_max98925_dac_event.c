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
struct snd_soc_dapm_widget {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct max98925_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int M98925_ADC_IMON_EN_MASK ; 
 int M98925_ADC_VMON_EN_MASK ; 
 int M98925_BST_EN_MASK ; 
 int /*<<< orphan*/  MAX98925_BLOCK_ENABLE ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct max98925_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int max98925_dac_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct max98925_priv *max98925 = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		regmap_update_bits(max98925->regmap,
			MAX98925_BLOCK_ENABLE,
			M98925_BST_EN_MASK |
			M98925_ADC_IMON_EN_MASK | M98925_ADC_VMON_EN_MASK,
			M98925_BST_EN_MASK |
			M98925_ADC_IMON_EN_MASK | M98925_ADC_VMON_EN_MASK);
		break;
	case SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(max98925->regmap,
			MAX98925_BLOCK_ENABLE, M98925_BST_EN_MASK |
			M98925_ADC_IMON_EN_MASK | M98925_ADC_VMON_EN_MASK, 0);
		break;
	default:
		return 0;
	}
	return 0;
}