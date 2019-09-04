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
struct snd_pcm_runtime {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  eld_limit_channels ; 
 int /*<<< orphan*/  eld_limit_rates ; 
 int snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 

int snd_pcm_hw_constraint_eld(struct snd_pcm_runtime *runtime, void *eld)
{
	int ret;

	ret = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				  eld_limit_rates, eld,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	if (ret < 0)
		return ret;

	ret = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				  eld_limit_channels, eld,
				  SNDRV_PCM_HW_PARAM_RATE, -1);

	return ret;
}