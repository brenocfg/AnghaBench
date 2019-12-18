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
typedef  int u16 ;
struct wm8960_priv {int /*<<< orphan*/  regmap; int /*<<< orphan*/  mclk; int /*<<< orphan*/  clk_id; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8960_APOP1 ; 
 int WM8960_BUFDCOPEN ; 
 int WM8960_BUFIOEN ; 
 int WM8960_POBCTRL ; 
 int /*<<< orphan*/  WM8960_POWER1 ; 
 int /*<<< orphan*/  WM8960_POWER2 ; 
 int WM8960_SOFT_ST ; 
 int /*<<< orphan*/  WM8960_SYSCLK_AUTO ; 
 int WM8960_VREF ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8960_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int wm8960_configure_clocking (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8960_set_pll (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8960_set_bias_level_out3(struct snd_soc_component *component,
				      enum snd_soc_bias_level level)
{
	struct wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	u16 pm2 = snd_soc_component_read32(component, WM8960_POWER2);
	int ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		switch (snd_soc_component_get_bias_level(component)) {
		case SND_SOC_BIAS_STANDBY:
			if (!IS_ERR(wm8960->mclk)) {
				ret = clk_prepare_enable(wm8960->mclk);
				if (ret) {
					dev_err(component->dev,
						"Failed to enable MCLK: %d\n",
						ret);
					return ret;
				}
			}

			ret = wm8960_configure_clocking(component);
			if (ret)
				return ret;

			/* Set VMID to 2x50k */
			snd_soc_component_update_bits(component, WM8960_POWER1, 0x180, 0x80);
			break;

		case SND_SOC_BIAS_ON:
			/*
			 * If it's sysclk auto mode, and the pll is enabled,
			 * disable the pll
			 */
			if (wm8960->clk_id == WM8960_SYSCLK_AUTO && (pm2 & 0x1))
				wm8960_set_pll(component, 0, 0);

			if (!IS_ERR(wm8960->mclk))
				clk_disable_unprepare(wm8960->mclk);
			break;

		default:
			break;
		}

		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			regcache_sync(wm8960->regmap);

			/* Enable anti-pop features */
			snd_soc_component_write(component, WM8960_APOP1,
				      WM8960_POBCTRL | WM8960_SOFT_ST |
				      WM8960_BUFDCOPEN | WM8960_BUFIOEN);

			/* Enable & ramp VMID at 2x50k */
			snd_soc_component_update_bits(component, WM8960_POWER1, 0x80, 0x80);
			msleep(100);

			/* Enable VREF */
			snd_soc_component_update_bits(component, WM8960_POWER1, WM8960_VREF,
					    WM8960_VREF);

			/* Disable anti-pop features */
			snd_soc_component_write(component, WM8960_APOP1, WM8960_BUFIOEN);
		}

		/* Set VMID to 2x250k */
		snd_soc_component_update_bits(component, WM8960_POWER1, 0x180, 0x100);
		break;

	case SND_SOC_BIAS_OFF:
		/* Enable anti-pop features */
		snd_soc_component_write(component, WM8960_APOP1,
			     WM8960_POBCTRL | WM8960_SOFT_ST |
			     WM8960_BUFDCOPEN | WM8960_BUFIOEN);

		/* Disable VMID and VREF, let them discharge */
		snd_soc_component_write(component, WM8960_POWER1, 0);
		msleep(600);
		break;
	}

	return 0;
}