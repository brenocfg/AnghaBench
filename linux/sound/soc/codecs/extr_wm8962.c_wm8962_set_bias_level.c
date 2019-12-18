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
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8962_PWR_MGMT_1 ; 
 int /*<<< orphan*/  WM8962_VMID_SEL_MASK ; 
 int /*<<< orphan*/  msleep (int) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8962_configure_bclk (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8962_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		/* VMID 2*50k */
		snd_soc_component_update_bits(component, WM8962_PWR_MGMT_1,
				    WM8962_VMID_SEL_MASK, 0x80);

		wm8962_configure_bclk(component);
		break;

	case SND_SOC_BIAS_STANDBY:
		/* VMID 2*250k */
		snd_soc_component_update_bits(component, WM8962_PWR_MGMT_1,
				    WM8962_VMID_SEL_MASK, 0x100);

		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			msleep(100);
		break;

	case SND_SOC_BIAS_OFF:
		break;
	}

	return 0;
}