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
struct wm8731_priv {int /*<<< orphan*/  regmap; int /*<<< orphan*/  supplies; int /*<<< orphan*/  mclk; } ;
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8731_PWR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8731_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8731_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct wm8731_priv *wm8731 = snd_soc_component_get_drvdata(component);
	int ret;
	u16 reg;

	switch (level) {
	case SND_SOC_BIAS_ON:
		if (wm8731->mclk) {
			ret = clk_prepare_enable(wm8731->mclk);
			if (ret)
				return ret;
		}
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8731->supplies),
						    wm8731->supplies);
			if (ret != 0)
				return ret;

			regcache_sync(wm8731->regmap);
		}

		/* Clear PWROFF, gate CLKOUT, everything else as-is */
		reg = snd_soc_component_read32(component, WM8731_PWR) & 0xff7f;
		snd_soc_component_write(component, WM8731_PWR, reg | 0x0040);
		break;
	case SND_SOC_BIAS_OFF:
		if (wm8731->mclk)
			clk_disable_unprepare(wm8731->mclk);
		snd_soc_component_write(component, WM8731_PWR, 0xffff);
		regulator_bulk_disable(ARRAY_SIZE(wm8731->supplies),
				       wm8731->supplies);
		regcache_mark_dirty(wm8731->regmap);
		break;
	}
	return 0;
}