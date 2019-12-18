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
struct wm9081_priv {int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM9081_ANTI_POP_CONTROL ; 
 int /*<<< orphan*/  WM9081_BIAS_CONTROL_1 ; 
 int WM9081_BIAS_ENA ; 
 int WM9081_BIAS_SRC ; 
 int WM9081_LINEOUT_DISCH ; 
 int WM9081_STBY_BIAS_ENA ; 
 int /*<<< orphan*/  WM9081_VMID_CONTROL ; 
 int WM9081_VMID_RAMP ; 
 int WM9081_VMID_SEL_MASK ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm9081_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm9081_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct wm9081_priv *wm9081 = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		/* VMID=2*40k */
		snd_soc_component_update_bits(component, WM9081_VMID_CONTROL,
				    WM9081_VMID_SEL_MASK, 0x2);

		/* Normal bias current */
		snd_soc_component_update_bits(component, WM9081_BIAS_CONTROL_1,
				    WM9081_STBY_BIAS_ENA, 0);
		break;

	case SND_SOC_BIAS_STANDBY:
		/* Initial cold start */
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			regcache_cache_only(wm9081->regmap, false);
			regcache_sync(wm9081->regmap);

			/* Disable LINEOUT discharge */
			snd_soc_component_update_bits(component, WM9081_ANTI_POP_CONTROL,
					    WM9081_LINEOUT_DISCH, 0);

			/* Select startup bias source */
			snd_soc_component_update_bits(component, WM9081_BIAS_CONTROL_1,
					    WM9081_BIAS_SRC | WM9081_BIAS_ENA,
					    WM9081_BIAS_SRC | WM9081_BIAS_ENA);

			/* VMID 2*4k; Soft VMID ramp enable */
			snd_soc_component_update_bits(component, WM9081_VMID_CONTROL,
					    WM9081_VMID_RAMP |
					    WM9081_VMID_SEL_MASK,
					    WM9081_VMID_RAMP | 0x6);

			mdelay(100);

			/* Normal bias enable & soft start off */
			snd_soc_component_update_bits(component, WM9081_VMID_CONTROL,
					    WM9081_VMID_RAMP, 0);

			/* Standard bias source */
			snd_soc_component_update_bits(component, WM9081_BIAS_CONTROL_1,
					    WM9081_BIAS_SRC, 0);
		}

		/* VMID 2*240k */
		snd_soc_component_update_bits(component, WM9081_VMID_CONTROL,
				    WM9081_VMID_SEL_MASK, 0x04);

		/* Standby bias current on */
		snd_soc_component_update_bits(component, WM9081_BIAS_CONTROL_1,
				    WM9081_STBY_BIAS_ENA,
				    WM9081_STBY_BIAS_ENA);
		break;

	case SND_SOC_BIAS_OFF:
		/* Startup bias source and disable bias */
		snd_soc_component_update_bits(component, WM9081_BIAS_CONTROL_1,
				    WM9081_BIAS_SRC | WM9081_BIAS_ENA,
				    WM9081_BIAS_SRC);

		/* Disable VMID with soft ramping */
		snd_soc_component_update_bits(component, WM9081_VMID_CONTROL,
				    WM9081_VMID_RAMP | WM9081_VMID_SEL_MASK,
				    WM9081_VMID_RAMP);

		/* Actively discharge LINEOUT */
		snd_soc_component_update_bits(component, WM9081_ANTI_POP_CONTROL,
				    WM9081_LINEOUT_DISCH,
				    WM9081_LINEOUT_DISCH);

		regcache_cache_only(wm9081->regmap, true);
		break;
	}

	return 0;
}