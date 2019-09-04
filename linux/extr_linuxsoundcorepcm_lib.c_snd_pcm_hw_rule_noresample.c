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
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAMS_NORESAMPLE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_hw_rule_noresample_func ; 

int snd_pcm_hw_rule_noresample(struct snd_pcm_runtime *runtime,
			       unsigned int base_rate)
{
	return snd_pcm_hw_rule_add(runtime, SNDRV_PCM_HW_PARAMS_NORESAMPLE,
				   SNDRV_PCM_HW_PARAM_RATE,
				   snd_pcm_hw_rule_noresample_func,
				   (void *)(uintptr_t)base_rate,
				   SNDRV_PCM_HW_PARAM_RATE, -1);
}