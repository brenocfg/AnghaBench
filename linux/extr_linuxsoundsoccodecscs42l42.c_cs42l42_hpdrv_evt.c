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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int CS42L42_ASP_DAI_PDN_MASK ; 
 int CS42L42_ASP_RX0_CH1_EN ; 
 int CS42L42_ASP_RX0_CH2_EN ; 
 int CS42L42_ASP_RX0_CH_EN_MASK ; 
 int CS42L42_ASP_RX0_CH_EN_SHIFT ; 
 int /*<<< orphan*/  CS42L42_ASP_RX_DAI0_EN ; 
 int CS42L42_HP_PDN_MASK ; 
 int CS42L42_MIXER_PDN_MASK ; 
 int /*<<< orphan*/  CS42L42_PWR_CTL1 ; 
 int SND_SOC_DAPM_POST_PMU ; 
 int SND_SOC_DAPM_PRE_PMD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs42l42_hpdrv_evt(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	if (event & SND_SOC_DAPM_POST_PMU) {
		/* Enable the channels */
		snd_soc_component_update_bits(component, CS42L42_ASP_RX_DAI0_EN,
				CS42L42_ASP_RX0_CH_EN_MASK,
				(CS42L42_ASP_RX0_CH1_EN |
				CS42L42_ASP_RX0_CH2_EN) <<
				CS42L42_ASP_RX0_CH_EN_SHIFT);

		/* Power up */
		snd_soc_component_update_bits(component, CS42L42_PWR_CTL1,
			CS42L42_ASP_DAI_PDN_MASK | CS42L42_MIXER_PDN_MASK |
				CS42L42_HP_PDN_MASK, 0);
	} else if (event & SND_SOC_DAPM_PRE_PMD) {
		/* Disable the channels */
		snd_soc_component_update_bits(component, CS42L42_ASP_RX_DAI0_EN,
				CS42L42_ASP_RX0_CH_EN_MASK, 0);

		/* Power down */
		snd_soc_component_update_bits(component, CS42L42_PWR_CTL1,
			CS42L42_ASP_DAI_PDN_MASK | CS42L42_MIXER_PDN_MASK |
				CS42L42_HP_PDN_MASK,
			CS42L42_ASP_DAI_PDN_MASK | CS42L42_MIXER_PDN_MASK |
				CS42L42_HP_PDN_MASK);
	} else {
		dev_err(component->dev, "Invalid event 0x%x\n", event);
	}
	return 0;
}