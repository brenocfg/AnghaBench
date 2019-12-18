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
struct snd_kcontrol {int dummy; } ;
struct arizona_priv {int /*<<< orphan*/  in_pending; } ;

/* Variables and functions */
 int ARIZONA_ADC_DIGITAL_VOLUME_1L ; 
 int ARIZONA_ADC_DIGITAL_VOLUME_1R ; 
 int ARIZONA_IN1L_MUTE ; 
 int /*<<< orphan*/  ARIZONA_INPUT_ENABLES ; 
 int ARIZONA_IN_VU ; 
#define  SND_SOC_DAPM_POST_PMD 131 
#define  SND_SOC_DAPM_POST_PMU 130 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  arizona_in_set_vu (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct arizona_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

int arizona_in_ev(struct snd_soc_dapm_widget *w, struct snd_kcontrol *kcontrol,
		  int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct arizona_priv *priv = snd_soc_component_get_drvdata(component);
	unsigned int reg;

	if (w->shift % 2)
		reg = ARIZONA_ADC_DIGITAL_VOLUME_1L + ((w->shift / 2) * 8);
	else
		reg = ARIZONA_ADC_DIGITAL_VOLUME_1R + ((w->shift / 2) * 8);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		priv->in_pending++;
		break;
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, reg,
					      ARIZONA_IN1L_MUTE, 0);

		/* If this is the last input pending then allow VU */
		priv->in_pending--;
		if (priv->in_pending == 0) {
			msleep(1);
			arizona_in_set_vu(component, 1);
		}
		break;
	case SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, reg,
				    ARIZONA_IN1L_MUTE | ARIZONA_IN_VU,
				    ARIZONA_IN1L_MUTE | ARIZONA_IN_VU);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* Disable volume updates if no inputs are enabled */
		reg = snd_soc_component_read32(component, ARIZONA_INPUT_ENABLES);
		if (reg == 0)
			arizona_in_set_vu(component, 0);
		break;
	default:
		break;
	}

	return 0;
}