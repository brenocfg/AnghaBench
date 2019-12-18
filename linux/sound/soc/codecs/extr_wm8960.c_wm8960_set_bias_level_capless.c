#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct wm8960_priv {int /*<<< orphan*/  regmap; int /*<<< orphan*/  mclk; int /*<<< orphan*/  clk_id; TYPE_3__* out3; TYPE_2__* rout1; TYPE_1__* lout1; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;
struct TYPE_6__ {int /*<<< orphan*/  power; } ;
struct TYPE_5__ {int /*<<< orphan*/  power; } ;
struct TYPE_4__ {int /*<<< orphan*/  power; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8960_APOP1 ; 
 int /*<<< orphan*/  WM8960_APOP2 ; 
 int WM8960_BUFDCOPEN ; 
 int WM8960_DISOP ; 
 int WM8960_DRES_MASK ; 
 int WM8960_POBCTRL ; 
 int /*<<< orphan*/  WM8960_POWER1 ; 
 int /*<<< orphan*/  WM8960_POWER2 ; 
 int WM8960_PWR2_LOUT1 ; 
 int WM8960_PWR2_OUT3 ; 
 int WM8960_PWR2_ROUT1 ; 
 int WM8960_SOFT_ST ; 
 int /*<<< orphan*/  WM8960_SYSCLK_AUTO ; 
 int WM8960_VMID_MASK ; 
 int WM8960_VREF ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8960_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int wm8960_configure_clocking (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8960_set_pll (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8960_set_bias_level_capless(struct snd_soc_component *component,
					 enum snd_soc_bias_level level)
{
	struct wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	u16 pm2 = snd_soc_component_read32(component, WM8960_POWER2);
	int reg, ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		switch (snd_soc_component_get_bias_level(component)) {
		case SND_SOC_BIAS_STANDBY:
			/* Enable anti pop mode */
			snd_soc_component_update_bits(component, WM8960_APOP1,
					    WM8960_POBCTRL | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN,
					    WM8960_POBCTRL | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN);

			/* Enable LOUT1, ROUT1 and OUT3 if they're enabled */
			reg = 0;
			if (wm8960->lout1 && wm8960->lout1->power)
				reg |= WM8960_PWR2_LOUT1;
			if (wm8960->rout1 && wm8960->rout1->power)
				reg |= WM8960_PWR2_ROUT1;
			if (wm8960->out3 && wm8960->out3->power)
				reg |= WM8960_PWR2_OUT3;
			snd_soc_component_update_bits(component, WM8960_POWER2,
					    WM8960_PWR2_LOUT1 |
					    WM8960_PWR2_ROUT1 |
					    WM8960_PWR2_OUT3, reg);

			/* Enable VMID at 2*50k */
			snd_soc_component_update_bits(component, WM8960_POWER1,
					    WM8960_VMID_MASK, 0x80);

			/* Ramp */
			msleep(100);

			/* Enable VREF */
			snd_soc_component_update_bits(component, WM8960_POWER1,
					    WM8960_VREF, WM8960_VREF);

			msleep(100);

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

			/* Enable anti-pop mode */
			snd_soc_component_update_bits(component, WM8960_APOP1,
					    WM8960_POBCTRL | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN,
					    WM8960_POBCTRL | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN);

			/* Disable VMID and VREF */
			snd_soc_component_update_bits(component, WM8960_POWER1,
					    WM8960_VREF | WM8960_VMID_MASK, 0);
			break;

		case SND_SOC_BIAS_OFF:
			regcache_sync(wm8960->regmap);
			break;
		default:
			break;
		}
		break;

	case SND_SOC_BIAS_STANDBY:
		switch (snd_soc_component_get_bias_level(component)) {
		case SND_SOC_BIAS_PREPARE:
			/* Disable HP discharge */
			snd_soc_component_update_bits(component, WM8960_APOP2,
					    WM8960_DISOP | WM8960_DRES_MASK,
					    0);

			/* Disable anti-pop features */
			snd_soc_component_update_bits(component, WM8960_APOP1,
					    WM8960_POBCTRL | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN,
					    WM8960_POBCTRL | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN);
			break;

		default:
			break;
		}
		break;

	case SND_SOC_BIAS_OFF:
		break;
	}

	return 0;
}