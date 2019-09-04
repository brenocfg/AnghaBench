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
typedef  unsigned int u8 ;
struct snd_pcm_hw_rule {unsigned int* private; int /*<<< orphan*/  var; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_interval {unsigned int min; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 unsigned int* drm_eld_sad (unsigned int const*) ; 
 unsigned int drm_eld_sad_count (unsigned int const*) ; 
 int /*<<< orphan*/  eld_rates ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 struct snd_interval* hw_param_interval_c (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 unsigned int sad_max_channels (unsigned int const*) ; 
 int snd_interval_list (struct snd_interval*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int eld_limit_rates(struct snd_pcm_hw_params *params,
			   struct snd_pcm_hw_rule *rule)
{
	struct snd_interval *r = hw_param_interval(params, rule->var);
	const struct snd_interval *c;
	unsigned int rate_mask = 7, i;
	const u8 *sad, *eld = rule->private;

	sad = drm_eld_sad(eld);
	if (sad) {
		c = hw_param_interval_c(params, SNDRV_PCM_HW_PARAM_CHANNELS);

		for (i = drm_eld_sad_count(eld); i > 0; i--, sad += 3) {
			unsigned max_channels = sad_max_channels(sad);

			/*
			 * Exclude SADs which do not include the
			 * requested number of channels.
			 */
			if (c->min <= max_channels)
				rate_mask |= sad[1];
		}
	}

	return snd_interval_list(r, ARRAY_SIZE(eld_rates), eld_rates,
				 rate_mask);
}