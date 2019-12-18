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
struct snd_pcm_hw_params {unsigned int rate_num; unsigned int rate_den; } ;
struct snd_interval {int min; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int snd_interval_ratnum (struct snd_interval*,int,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  stereo_clocks ; 

__attribute__((used)) static int snd_sb8_hw_constraint_rate_channels(struct snd_pcm_hw_params *params,
					       struct snd_pcm_hw_rule *rule)
{
	struct snd_interval *c = hw_param_interval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	if (c->min > 1) {
	  	unsigned int num = 0, den = 0;
		int err = snd_interval_ratnum(hw_param_interval(params, SNDRV_PCM_HW_PARAM_RATE),
					  2, stereo_clocks, &num, &den);
		if (err >= 0 && den) {
			params->rate_num = num;
			params->rate_den = den;
		}
		return err;
	}
	return 0;
}