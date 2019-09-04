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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int rmask; scalar_t__ rate_den; scalar_t__ rate_num; scalar_t__ msbits; scalar_t__ fifo_size; scalar_t__ info; } ;

/* Variables and functions */
 int SNDRV_PCM_HW_PARAM_RATE ; 
 int SNDRV_PCM_HW_PARAM_SAMPLE_BITS ; 
 int constrain_interval_params (struct snd_pcm_substream*,struct snd_pcm_hw_params*) ; 
 int constrain_mask_params (struct snd_pcm_substream*,struct snd_pcm_hw_params*) ; 
 int constrain_params_by_rules (struct snd_pcm_substream*,struct snd_pcm_hw_params*) ; 

int snd_pcm_hw_refine(struct snd_pcm_substream *substream,
		      struct snd_pcm_hw_params *params)
{
	int err;

	params->info = 0;
	params->fifo_size = 0;
	if (params->rmask & (1 << SNDRV_PCM_HW_PARAM_SAMPLE_BITS))
		params->msbits = 0;
	if (params->rmask & (1 << SNDRV_PCM_HW_PARAM_RATE)) {
		params->rate_num = 0;
		params->rate_den = 0;
	}

	err = constrain_mask_params(substream, params);
	if (err < 0)
		return err;

	err = constrain_interval_params(substream, params);
	if (err < 0)
		return err;

	err = constrain_params_by_rules(substream, params);
	if (err < 0)
		return err;

	params->rmask = 0;

	return 0;
}