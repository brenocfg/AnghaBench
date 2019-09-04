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
typedef  int u32 ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int SGTL5000_ADC_POWERUP ; 
 int /*<<< orphan*/  SGTL5000_CHIP_ANA_POWER ; 
 int SGTL5000_DAC_POWERUP ; 
 int /*<<< orphan*/  SGTL5000_VAG_POWERUP ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  msleep (int) ; 
 int const snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int power_vag_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	const u32 mask = SGTL5000_DAC_POWERUP | SGTL5000_ADC_POWERUP;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, SGTL5000_CHIP_ANA_POWER,
			SGTL5000_VAG_POWERUP, SGTL5000_VAG_POWERUP);
		msleep(400);
		break;

	case SND_SOC_DAPM_PRE_PMD:
		/*
		 * Don't clear VAG_POWERUP, when both DAC and ADC are
		 * operational to prevent inadvertently starving the
		 * other one of them.
		 */
		if ((snd_soc_component_read32(component, SGTL5000_CHIP_ANA_POWER) &
				mask) != mask) {
			snd_soc_component_update_bits(component, SGTL5000_CHIP_ANA_POWER,
				SGTL5000_VAG_POWERUP, 0);
			msleep(400);
		}
		break;
	default:
		break;
	}

	return 0;
}