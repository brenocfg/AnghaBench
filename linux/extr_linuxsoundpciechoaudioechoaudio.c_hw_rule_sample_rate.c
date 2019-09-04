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
struct snd_pcm_hw_rule {struct echoaudio* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_interval {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct echoaudio {int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  can_set_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_interval_any (struct snd_interval*) ; 
 int snd_interval_refine (struct snd_interval*,struct snd_interval*) ; 

__attribute__((used)) static int hw_rule_sample_rate(struct snd_pcm_hw_params *params,
			       struct snd_pcm_hw_rule *rule)
{
	struct snd_interval *rate = hw_param_interval(params,
						      SNDRV_PCM_HW_PARAM_RATE);
	struct echoaudio *chip = rule->private;
	struct snd_interval fixed;

	if (!chip->can_set_rate) {
		snd_interval_any(&fixed);
		fixed.min = fixed.max = chip->sample_rate;
		return snd_interval_refine(rate, &fixed);
	}
	return 0;
}