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
struct snd_soc_dapm_widget {int on_val; int /*<<< orphan*/  shift; int /*<<< orphan*/  regulator; int /*<<< orphan*/  name; TYPE_1__* dapm; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int SND_SOC_DAPM_REGULATOR_BYPASS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int regulator_allow_bypass (int /*<<< orphan*/ ,int) ; 
 int regulator_disable_deferred (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_dapm_async_complete (TYPE_1__*) ; 

int dapm_regulator_event(struct snd_soc_dapm_widget *w,
		   struct snd_kcontrol *kcontrol, int event)
{
	int ret;

	soc_dapm_async_complete(w->dapm);

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		if (w->on_val & SND_SOC_DAPM_REGULATOR_BYPASS) {
			ret = regulator_allow_bypass(w->regulator, false);
			if (ret != 0)
				dev_warn(w->dapm->dev,
					 "ASoC: Failed to unbypass %s: %d\n",
					 w->name, ret);
		}

		return regulator_enable(w->regulator);
	} else {
		if (w->on_val & SND_SOC_DAPM_REGULATOR_BYPASS) {
			ret = regulator_allow_bypass(w->regulator, true);
			if (ret != 0)
				dev_warn(w->dapm->dev,
					 "ASoC: Failed to bypass %s: %d\n",
					 w->name, ret);
		}

		return regulator_disable_deferred(w->regulator, w->shift);
	}
}