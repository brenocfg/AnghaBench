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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_A_MICB_1_EN ; 
 int /*<<< orphan*/  MICB_1_EN_BYP_CAP_MASK ; 
#define  SND_SOC_DAPM_POST_PMU 128 
 int /*<<< orphan*/  pm8916_wcd_analog_micbias_enable (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int pm8916_wcd_analog_enable_micbias_ext(struct snd_soc_component
						 *component, int event,
						 int reg, unsigned int cap_mode)
{
	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		pm8916_wcd_analog_micbias_enable(component);
		snd_soc_component_update_bits(component, CDC_A_MICB_1_EN,
				    MICB_1_EN_BYP_CAP_MASK, cap_mode);
		break;
	}

	return 0;
}