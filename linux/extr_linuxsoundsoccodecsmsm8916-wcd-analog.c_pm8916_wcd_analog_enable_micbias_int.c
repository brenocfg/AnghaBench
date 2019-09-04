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
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int CDC_A_MICB_1_EN ; 
 int CDC_A_MICB_1_INT_RBIAS ; 
 int /*<<< orphan*/  MICB_1_EN_BYP_CAP_MASK ; 
 int /*<<< orphan*/  MICB_1_EN_OPA_STG2_TAIL_CURR_1_60UA ; 
 int /*<<< orphan*/  MICB_1_EN_OPA_STG2_TAIL_CURR_MASK ; 
 int /*<<< orphan*/  MICB_1_EN_PULL_DOWN_EN_MASK ; 
 int /*<<< orphan*/  MICB_1_INT_TX2_INT_RBIAS_EN_ENABLE ; 
 int /*<<< orphan*/  MICB_1_INT_TX2_INT_RBIAS_EN_MASK ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  pm8916_wcd_analog_micbias_enable (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm8916_wcd_analog_enable_micbias_int(struct snd_soc_component
						 *component, int event,
						 int reg, u32 cap_mode)
{

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, CDC_A_MICB_1_INT_RBIAS,
				    MICB_1_INT_TX2_INT_RBIAS_EN_MASK,
				    MICB_1_INT_TX2_INT_RBIAS_EN_ENABLE);
		snd_soc_component_update_bits(component, reg, MICB_1_EN_PULL_DOWN_EN_MASK, 0);
		snd_soc_component_update_bits(component, CDC_A_MICB_1_EN,
				    MICB_1_EN_OPA_STG2_TAIL_CURR_MASK,
				    MICB_1_EN_OPA_STG2_TAIL_CURR_1_60UA);

		break;
	case SND_SOC_DAPM_POST_PMU:
		pm8916_wcd_analog_micbias_enable(component);
		snd_soc_component_update_bits(component, CDC_A_MICB_1_EN,
				    MICB_1_EN_BYP_CAP_MASK, cap_mode);
		break;
	}

	return 0;
}