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
struct snd_soc_dapm_widget {int /*<<< orphan*/  reg; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA732X_ADCA_BB_CLK_EN ; 
 int /*<<< orphan*/  DA732X_ADCC_BB_CLK_EN ; 
 int /*<<< orphan*/  DA732X_ADC_OFF ; 
 int /*<<< orphan*/  DA732X_ADC_ON ; 
 int /*<<< orphan*/  DA732X_ADC_PD_MASK ; 
 int /*<<< orphan*/  DA732X_ADC_RST_MASK ; 
 int /*<<< orphan*/  DA732X_ADC_SET_ACT ; 
 int /*<<< orphan*/  DA732X_ADC_SET_RST ; 
#define  DA732X_REG_ADC1_PD 131 
#define  DA732X_REG_ADC2_PD 130 
 int /*<<< orphan*/  DA732X_REG_CLK_EN3 ; 
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_POST_PMU 128 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da732x_adc_event(struct snd_soc_dapm_widget *w,
			    struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		switch (w->reg) {
		case DA732X_REG_ADC1_PD:
			snd_soc_component_update_bits(component, DA732X_REG_CLK_EN3,
					    DA732X_ADCA_BB_CLK_EN,
					    DA732X_ADCA_BB_CLK_EN);
			break;
		case DA732X_REG_ADC2_PD:
			snd_soc_component_update_bits(component, DA732X_REG_CLK_EN3,
					    DA732X_ADCC_BB_CLK_EN,
					    DA732X_ADCC_BB_CLK_EN);
			break;
		default:
			return -EINVAL;
		}

		snd_soc_component_update_bits(component, w->reg, DA732X_ADC_RST_MASK,
				    DA732X_ADC_SET_ACT);
		snd_soc_component_update_bits(component, w->reg, DA732X_ADC_PD_MASK,
				    DA732X_ADC_ON);
		break;
	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, w->reg, DA732X_ADC_PD_MASK,
				    DA732X_ADC_OFF);
		snd_soc_component_update_bits(component, w->reg, DA732X_ADC_RST_MASK,
				    DA732X_ADC_SET_RST);

		switch (w->reg) {
		case DA732X_REG_ADC1_PD:
			snd_soc_component_update_bits(component, DA732X_REG_CLK_EN3,
					    DA732X_ADCA_BB_CLK_EN, 0);
			break;
		case DA732X_REG_ADC2_PD:
			snd_soc_component_update_bits(component, DA732X_REG_CLK_EN3,
					    DA732X_ADCC_BB_CLK_EN, 0);
			break;
		default:
			return -EINVAL;
		}

		break;
	default:
		return -EINVAL;
	}

	return 0;
}