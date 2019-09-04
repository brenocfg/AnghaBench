#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dapm_widget {TYPE_1__* dapm; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP3_PANDORA_DAC_POWER_GPIO ; 
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  omap3pandora_dac_reg ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap3pandora_dac_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *k, int event)
{
	int ret;

	/*
	 * The PCM1773 DAC datasheet requires 1ms delay between switching
	 * VCC power on/off and /PD pin high/low
	 */
	if (SND_SOC_DAPM_EVENT_ON(event)) {
		ret = regulator_enable(omap3pandora_dac_reg);
		if (ret) {
			dev_err(w->dapm->dev, "Failed to power DAC: %d\n", ret);
			return ret;
		}
		mdelay(1);
		gpio_set_value(OMAP3_PANDORA_DAC_POWER_GPIO, 1);
	} else {
		gpio_set_value(OMAP3_PANDORA_DAC_POWER_GPIO, 0);
		mdelay(1);
		regulator_disable(omap3pandora_dac_reg);
	}

	return 0;
}