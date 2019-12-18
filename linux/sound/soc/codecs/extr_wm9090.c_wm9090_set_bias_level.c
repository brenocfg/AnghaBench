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
struct wm9090_priv {int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM9090_ANTIPOP2 ; 
 int WM9090_BIAS_ENA ; 
 int /*<<< orphan*/  WM9090_POWER_MANAGEMENT_1 ; 
 int WM9090_VMID_ENA ; 
 int WM9090_VMID_RES_MASK ; 
 int WM9090_VMID_RES_SHIFT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm9090_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm9090_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct wm9090_priv *wm9090 = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		snd_soc_component_update_bits(component, WM9090_ANTIPOP2, WM9090_VMID_ENA,
				    WM9090_VMID_ENA);
		snd_soc_component_update_bits(component, WM9090_POWER_MANAGEMENT_1,
				    WM9090_BIAS_ENA |
				    WM9090_VMID_RES_MASK,
				    WM9090_BIAS_ENA |
				    1 << WM9090_VMID_RES_SHIFT);
		msleep(1);  /* Probably an overestimate */
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			/* Restore the register cache */
			regcache_sync(wm9090->regmap);
		}

		/* We keep VMID off during standby since the combination of
		 * ground referenced outputs and class D speaker mean that
		 * latency is not an issue.
		 */
		snd_soc_component_update_bits(component, WM9090_POWER_MANAGEMENT_1,
				    WM9090_BIAS_ENA | WM9090_VMID_RES_MASK, 0);
		snd_soc_component_update_bits(component, WM9090_ANTIPOP2,
				    WM9090_VMID_ENA, 0);
		break;

	case SND_SOC_BIAS_OFF:
		break;
	}

	return 0;
}