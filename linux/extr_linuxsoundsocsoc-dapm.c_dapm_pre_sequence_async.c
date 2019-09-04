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
struct snd_soc_dapm_context {scalar_t__ bias_level; scalar_t__ target_bias_level; scalar_t__ dev; } ;
typedef  int /*<<< orphan*/  async_cookie_t ;

/* Variables and functions */
 scalar_t__ SND_SOC_BIAS_OFF ; 
 scalar_t__ SND_SOC_BIAS_ON ; 
 int /*<<< orphan*/  SND_SOC_BIAS_PREPARE ; 
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  dev_err (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (scalar_t__) ; 
 int snd_soc_dapm_set_bias_level (struct snd_soc_dapm_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dapm_pre_sequence_async(void *data, async_cookie_t cookie)
{
	struct snd_soc_dapm_context *d = data;
	int ret;

	/* If we're off and we're not supposed to go into STANDBY */
	if (d->bias_level == SND_SOC_BIAS_OFF &&
	    d->target_bias_level != SND_SOC_BIAS_OFF) {
		if (d->dev)
			pm_runtime_get_sync(d->dev);

		ret = snd_soc_dapm_set_bias_level(d, SND_SOC_BIAS_STANDBY);
		if (ret != 0)
			dev_err(d->dev,
				"ASoC: Failed to turn on bias: %d\n", ret);
	}

	/* Prepare for a transition to ON or away from ON */
	if ((d->target_bias_level == SND_SOC_BIAS_ON &&
	     d->bias_level != SND_SOC_BIAS_ON) ||
	    (d->target_bias_level != SND_SOC_BIAS_ON &&
	     d->bias_level == SND_SOC_BIAS_ON)) {
		ret = snd_soc_dapm_set_bias_level(d, SND_SOC_BIAS_PREPARE);
		if (ret != 0)
			dev_err(d->dev,
				"ASoC: Failed to prepare bias: %d\n", ret);
	}
}