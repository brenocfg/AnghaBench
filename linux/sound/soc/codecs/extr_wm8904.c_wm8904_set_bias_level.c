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
struct wm8904_priv {int /*<<< orphan*/  mclk; int /*<<< orphan*/  supplies; int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8904_BIAS_CONTROL_0 ; 
 int WM8904_BIAS_ENA ; 
 int WM8904_ISEL_MASK ; 
 int WM8904_ISEL_SHIFT ; 
 int /*<<< orphan*/  WM8904_VMID_CONTROL_0 ; 
 int WM8904_VMID_ENA ; 
 int WM8904_VMID_RES_MASK ; 
 int WM8904_VMID_RES_SHIFT ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8904_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm8904_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	int ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		/* VMID resistance 2*50k */
		snd_soc_component_update_bits(component, WM8904_VMID_CONTROL_0,
				    WM8904_VMID_RES_MASK,
				    0x1 << WM8904_VMID_RES_SHIFT);

		/* Normal bias current */
		snd_soc_component_update_bits(component, WM8904_BIAS_CONTROL_0,
				    WM8904_ISEL_MASK, 2 << WM8904_ISEL_SHIFT);
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8904->supplies),
						    wm8904->supplies);
			if (ret != 0) {
				dev_err(component->dev,
					"Failed to enable supplies: %d\n",
					ret);
				return ret;
			}

			ret = clk_prepare_enable(wm8904->mclk);
			if (ret) {
				dev_err(component->dev,
					"Failed to enable MCLK: %d\n", ret);
				regulator_bulk_disable(ARRAY_SIZE(wm8904->supplies),
						       wm8904->supplies);
				return ret;
			}

			regcache_cache_only(wm8904->regmap, false);
			regcache_sync(wm8904->regmap);

			/* Enable bias */
			snd_soc_component_update_bits(component, WM8904_BIAS_CONTROL_0,
					    WM8904_BIAS_ENA, WM8904_BIAS_ENA);

			/* Enable VMID, VMID buffering, 2*5k resistance */
			snd_soc_component_update_bits(component, WM8904_VMID_CONTROL_0,
					    WM8904_VMID_ENA |
					    WM8904_VMID_RES_MASK,
					    WM8904_VMID_ENA |
					    0x3 << WM8904_VMID_RES_SHIFT);

			/* Let VMID ramp */
			msleep(1);
		}

		/* Maintain VMID with 2*250k */
		snd_soc_component_update_bits(component, WM8904_VMID_CONTROL_0,
				    WM8904_VMID_RES_MASK,
				    0x2 << WM8904_VMID_RES_SHIFT);

		/* Bias current *0.5 */
		snd_soc_component_update_bits(component, WM8904_BIAS_CONTROL_0,
				    WM8904_ISEL_MASK, 0);
		break;

	case SND_SOC_BIAS_OFF:
		/* Turn off VMID */
		snd_soc_component_update_bits(component, WM8904_VMID_CONTROL_0,
				    WM8904_VMID_RES_MASK | WM8904_VMID_ENA, 0);

		/* Stop bias generation */
		snd_soc_component_update_bits(component, WM8904_BIAS_CONTROL_0,
				    WM8904_BIAS_ENA, 0);

		regcache_cache_only(wm8904->regmap, true);
		regcache_mark_dirty(wm8904->regmap);

		regulator_bulk_disable(ARRAY_SIZE(wm8904->supplies),
				       wm8904->supplies);
		clk_disable_unprepare(wm8904->mclk);
		break;
	}
	return 0;
}