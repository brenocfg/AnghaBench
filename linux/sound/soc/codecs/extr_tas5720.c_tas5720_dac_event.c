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
struct tas5720_data {int /*<<< orphan*/  fault_check_work; scalar_t__ last_fault; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int SND_SOC_DAPM_POST_PMU ; 
 int SND_SOC_DAPM_PRE_PMD ; 
 int /*<<< orphan*/  TAS5720_FAULT_CHECK_INTERVAL ; 
 int /*<<< orphan*/  TAS5720_POWER_CTRL_REG ; 
 int /*<<< orphan*/  TAS5720_SDZ ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tas5720_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tas5720_dac_event(struct snd_soc_dapm_widget *w,
			     struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct tas5720_data *tas5720 = snd_soc_component_get_drvdata(component);
	int ret;

	if (event & SND_SOC_DAPM_POST_PMU) {
		/* Take TAS5720 out of shutdown mode */
		ret = snd_soc_component_update_bits(component, TAS5720_POWER_CTRL_REG,
					  TAS5720_SDZ, TAS5720_SDZ);
		if (ret < 0) {
			dev_err(component->dev, "error waking component: %d\n", ret);
			return ret;
		}

		/*
		 * Observe codec shutdown-to-active time. The datasheet only
		 * lists a nominal value however just use-it as-is without
		 * additional padding to minimize the delay introduced in
		 * starting to play audio (actually there is other setup done
		 * by the ASoC framework that will provide additional delays,
		 * so we should always be safe).
		 */
		msleep(25);

		/* Turn on TAS5720 periodic fault checking/handling */
		tas5720->last_fault = 0;
		schedule_delayed_work(&tas5720->fault_check_work,
				msecs_to_jiffies(TAS5720_FAULT_CHECK_INTERVAL));
	} else if (event & SND_SOC_DAPM_PRE_PMD) {
		/* Disable TAS5720 periodic fault checking/handling */
		cancel_delayed_work_sync(&tas5720->fault_check_work);

		/* Place TAS5720 in shutdown mode to minimize current draw */
		ret = snd_soc_component_update_bits(component, TAS5720_POWER_CTRL_REG,
					  TAS5720_SDZ, 0);
		if (ret < 0) {
			dev_err(component->dev, "error shutting down component: %d\n",
				ret);
			return ret;
		}
	}

	return 0;
}