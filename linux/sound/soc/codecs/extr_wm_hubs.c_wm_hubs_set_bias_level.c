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
struct wm_hubs_data {int /*<<< orphan*/  lineout2p_ena; int /*<<< orphan*/  lineout2_se; int /*<<< orphan*/  lineout2n_ena; int /*<<< orphan*/  lineout1p_ena; int /*<<< orphan*/  lineout1_se; int /*<<< orphan*/  lineout1n_ena; } ;
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_ON 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int WM8993_INPUTS_CLAMP ; 
 int /*<<< orphan*/  WM8993_INPUTS_CLAMP_REG ; 
 int WM8993_LINEOUT1N_ENA ; 
 int WM8993_LINEOUT1P_ENA ; 
 int WM8993_LINEOUT2N_ENA ; 
 int WM8993_LINEOUT2P_ENA ; 
 int /*<<< orphan*/  WM8993_POWER_MANAGEMENT_3 ; 
 struct wm_hubs_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

void wm_hubs_set_bias_level(struct snd_soc_component *component,
			    enum snd_soc_bias_level level)
{
	struct wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	int mask, val;

	switch (level) {
	case SND_SOC_BIAS_STANDBY:
		/* Clamp the inputs to VMID while we ramp to charge caps */
		snd_soc_component_update_bits(component, WM8993_INPUTS_CLAMP_REG,
				    WM8993_INPUTS_CLAMP, WM8993_INPUTS_CLAMP);
		break;

	case SND_SOC_BIAS_ON:
		/* Turn off any unneeded single ended outputs */
		val = 0;
		mask = 0;

		if (hubs->lineout1_se)
			mask |= WM8993_LINEOUT1N_ENA | WM8993_LINEOUT1P_ENA;

		if (hubs->lineout2_se)
			mask |= WM8993_LINEOUT2N_ENA | WM8993_LINEOUT2P_ENA;

		if (hubs->lineout1_se && hubs->lineout1n_ena)
			val |= WM8993_LINEOUT1N_ENA;

		if (hubs->lineout1_se && hubs->lineout1p_ena)
			val |= WM8993_LINEOUT1P_ENA;

		if (hubs->lineout2_se && hubs->lineout2n_ena)
			val |= WM8993_LINEOUT2N_ENA;

		if (hubs->lineout2_se && hubs->lineout2p_ena)
			val |= WM8993_LINEOUT2P_ENA;

		snd_soc_component_update_bits(component, WM8993_POWER_MANAGEMENT_3,
				    mask, val);

		/* Remove the input clamps */
		snd_soc_component_update_bits(component, WM8993_INPUTS_CLAMP_REG,
				    WM8993_INPUTS_CLAMP, 0);
		break;

	default:
		break;
	}
}