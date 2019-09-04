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
struct nau8825 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NAU8825_BIAS_TESTDAC_EN ; 
 int /*<<< orphan*/  NAU8825_REG_BIAS_ADJ ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nau8825* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nau8825_output_dac_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct nau8825 *nau8825 = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* Disables the TESTDAC to let DAC signal pass through. */
		regmap_update_bits(nau8825->regmap, NAU8825_REG_BIAS_ADJ,
			NAU8825_BIAS_TESTDAC_EN, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(nau8825->regmap, NAU8825_REG_BIAS_ADJ,
			NAU8825_BIAS_TESTDAC_EN, NAU8825_BIAS_TESTDAC_EN);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}