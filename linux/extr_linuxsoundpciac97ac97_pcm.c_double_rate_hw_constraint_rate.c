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
struct snd_pcm_hw_rule {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_interval {int min; int max; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int snd_interval_refine (struct snd_interval*,struct snd_interval const*) ; 

__attribute__((used)) static int double_rate_hw_constraint_rate(struct snd_pcm_hw_params *params,
					  struct snd_pcm_hw_rule *rule)
{
	struct snd_interval *channels = hw_param_interval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	if (channels->min > 2) {
		static const struct snd_interval single_rates = {
			.min = 1,
			.max = 48000,
		};
		struct snd_interval *rate = hw_param_interval(params, SNDRV_PCM_HW_PARAM_RATE);
		return snd_interval_refine(rate, &single_rates);
	}
	return 0;
}