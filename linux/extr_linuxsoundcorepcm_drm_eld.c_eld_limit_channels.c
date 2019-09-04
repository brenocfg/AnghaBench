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
struct snd_interval {int min; int max; int integer; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 unsigned int BIT (unsigned int) ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 unsigned int* drm_eld_sad (unsigned int const*) ; 
 unsigned int drm_eld_sad_count (unsigned int const*) ; 
 scalar_t__* eld_rates ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 struct snd_interval* hw_param_interval_c (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 scalar_t__ max (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sad_max_channels (unsigned int const*) ; 
 int snd_interval_refine (struct snd_interval*,struct snd_interval*) ; 

__attribute__((used)) static int eld_limit_channels(struct snd_pcm_hw_params *params,
			      struct snd_pcm_hw_rule *rule)
{
	struct snd_interval *c = hw_param_interval(params, rule->var);
	const struct snd_interval *r;
	struct snd_interval t = { .min = 1, .max = 2, .integer = 1, };
	unsigned int i;
	const u8 *sad, *eld = rule->private;

	sad = drm_eld_sad(eld);
	if (sad) {
		unsigned int rate_mask = 0;

		/* Convert the rate interval to a mask */
		r = hw_param_interval_c(params, SNDRV_PCM_HW_PARAM_RATE);
		for (i = 0; i < ARRAY_SIZE(eld_rates); i++)
			if (r->min <= eld_rates[i] && r->max >= eld_rates[i])
				rate_mask |= BIT(i);

		for (i = drm_eld_sad_count(eld); i > 0; i--, sad += 3)
			if (rate_mask & sad[1])
				t.max = max(t.max, sad_max_channels(sad));
	}

	return snd_interval_refine(c, &t);
}