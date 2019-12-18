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
 scalar_t__ SND_SOC_BIAS_PREPARE ; 
 scalar_t__ SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  dev_err (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  pm_runtime_put (scalar_t__) ; 
 int snd_soc_dapm_set_bias_level (struct snd_soc_dapm_context*,scalar_t__) ; 

__attribute__((used)) static void dapm_post_sequence_async(void *data, async_cookie_t cookie)
{
	struct snd_soc_dapm_context *d = data;
	int ret;

	/* If we just powered the last thing off drop to standby bias */
	if (d->bias_level == SND_SOC_BIAS_PREPARE &&
	    (d->target_bias_level == SND_SOC_BIAS_STANDBY ||
	     d->target_bias_level == SND_SOC_BIAS_OFF)) {
		ret = snd_soc_dapm_set_bias_level(d, SND_SOC_BIAS_STANDBY);
		if (ret != 0)
			dev_err(d->dev, "ASoC: Failed to apply standby bias: %d\n",
				ret);
	}

	/* If we're in standby and can support bias off then do that */
	if (d->bias_level == SND_SOC_BIAS_STANDBY &&
	    d->target_bias_level == SND_SOC_BIAS_OFF) {
		ret = snd_soc_dapm_set_bias_level(d, SND_SOC_BIAS_OFF);
		if (ret != 0)
			dev_err(d->dev, "ASoC: Failed to turn off bias: %d\n",
				ret);

		if (d->dev)
			pm_runtime_put(d->dev);
	}

	/* If we just powered up then move to active bias */
	if (d->bias_level == SND_SOC_BIAS_PREPARE &&
	    d->target_bias_level == SND_SOC_BIAS_ON) {
		ret = snd_soc_dapm_set_bias_level(d, SND_SOC_BIAS_ON);
		if (ret != 0)
			dev_err(d->dev, "ASoC: Failed to apply active bias: %d\n",
				ret);
	}
}