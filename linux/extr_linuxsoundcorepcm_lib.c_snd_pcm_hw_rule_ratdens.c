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
struct snd_pcm_hw_rule {scalar_t__ var; struct snd_pcm_hw_constraint_ratdens* private; } ;
struct snd_pcm_hw_params {unsigned int rate_num; unsigned int rate_den; } ;
struct snd_pcm_hw_constraint_ratdens {int /*<<< orphan*/  rats; int /*<<< orphan*/  nrats; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  hw_param_interval (struct snd_pcm_hw_params*,scalar_t__) ; 
 int snd_interval_ratden (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int snd_pcm_hw_rule_ratdens(struct snd_pcm_hw_params *params,
				   struct snd_pcm_hw_rule *rule)
{
	const struct snd_pcm_hw_constraint_ratdens *r = rule->private;
	unsigned int num = 0, den = 0;
	int err = snd_interval_ratden(hw_param_interval(params, rule->var),
				  r->nrats, r->rats, &num, &den);
	if (err >= 0 && den && rule->var == SNDRV_PCM_HW_PARAM_RATE) {
		params->rate_num = num;
		params->rate_den = den;
	}
	return err;
}