#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_pcm_hw_params {int rmask; int cmask; } ;
struct snd_pcm_hw_constraints {int dummy; } ;
struct snd_interval {int dummy; } ;
struct TYPE_2__ {struct snd_pcm_hw_constraints hw_constraints; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SNDRV_PCM_HW_PARAM_FIRST_INTERVAL ; 
 unsigned int SNDRV_PCM_HW_PARAM_LAST_INTERVAL ; 
 int /*<<< orphan*/  constrs_interval (struct snd_pcm_hw_constraints*,unsigned int) ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,unsigned int) ; 
 scalar_t__ snd_interval_empty (struct snd_interval*) ; 
 int snd_interval_refine (struct snd_interval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hw_interval_param (struct snd_pcm_substream*,unsigned int,int /*<<< orphan*/ ,struct snd_interval*,struct snd_interval*) ; 
 scalar_t__ trace_hw_interval_param_enabled () ; 

__attribute__((used)) static int constrain_interval_params(struct snd_pcm_substream *substream,
				     struct snd_pcm_hw_params *params)
{
	struct snd_pcm_hw_constraints *constrs =
					&substream->runtime->hw_constraints;
	struct snd_interval *i;
	unsigned int k;
	struct snd_interval old_interval;
	int changed;

	for (k = SNDRV_PCM_HW_PARAM_FIRST_INTERVAL; k <= SNDRV_PCM_HW_PARAM_LAST_INTERVAL; k++) {
		i = hw_param_interval(params, k);
		if (snd_interval_empty(i))
			return -EINVAL;

		/* This parameter is not requested to change by a caller. */
		if (!(params->rmask & (1 << k)))
			continue;

		if (trace_hw_interval_param_enabled())
			old_interval = *i;

		changed = snd_interval_refine(i, constrs_interval(constrs, k));
		if (changed < 0)
			return changed;
		if (changed == 0)
			continue;

		/* Set corresponding flag so that the caller gets it. */
		trace_hw_interval_param(substream, k, 0, &old_interval, i);
		params->cmask |= 1 << k;
	}

	return 0;
}