#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_3__* runtime; TYPE_1__* ops; } ;
struct snd_pcm_hw_params {int rate_den; int info; int /*<<< orphan*/  fifo_size; void* rate_num; void* msbits; } ;
struct snd_mask {int dummy; } ;
struct snd_interval {int dummy; } ;
struct TYPE_5__ {int info; } ;
struct TYPE_6__ {TYPE_2__ hw; } ;
struct TYPE_4__ {int (* ioctl ) (struct snd_pcm_substream*,int /*<<< orphan*/ ,struct snd_pcm_hw_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_SAMPLE_BITS ; 
 int SNDRV_PCM_INFO_DRAIN_TRIGGER ; 
 int SNDRV_PCM_INFO_FIFO_IN_FRAMES ; 
 int SNDRV_PCM_INFO_MMAP ; 
 int SNDRV_PCM_INFO_MMAP_VALID ; 
 int /*<<< orphan*/  SNDRV_PCM_IOCTL1_FIFO_SIZE ; 
 struct snd_interval* hw_param_interval_c (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 struct snd_mask* hw_param_mask_c (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_support_mmap (struct snd_pcm_substream*) ; 
 scalar_t__ snd_interval_single (struct snd_interval const*) ; 
 void* snd_interval_value (struct snd_interval const*) ; 
 scalar_t__ snd_mask_single (struct snd_mask const*) ; 
 int stub1 (struct snd_pcm_substream*,int /*<<< orphan*/ ,struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int fixup_unreferenced_params(struct snd_pcm_substream *substream,
				     struct snd_pcm_hw_params *params)
{
	const struct snd_interval *i;
	const struct snd_mask *m;
	int err;

	if (!params->msbits) {
		i = hw_param_interval_c(params, SNDRV_PCM_HW_PARAM_SAMPLE_BITS);
		if (snd_interval_single(i))
			params->msbits = snd_interval_value(i);
	}

	if (!params->rate_den) {
		i = hw_param_interval_c(params, SNDRV_PCM_HW_PARAM_RATE);
		if (snd_interval_single(i)) {
			params->rate_num = snd_interval_value(i);
			params->rate_den = 1;
		}
	}

	if (!params->fifo_size) {
		m = hw_param_mask_c(params, SNDRV_PCM_HW_PARAM_FORMAT);
		i = hw_param_interval_c(params, SNDRV_PCM_HW_PARAM_CHANNELS);
		if (snd_mask_single(m) && snd_interval_single(i)) {
			err = substream->ops->ioctl(substream,
					SNDRV_PCM_IOCTL1_FIFO_SIZE, params);
			if (err < 0)
				return err;
		}
	}

	if (!params->info) {
		params->info = substream->runtime->hw.info;
		params->info &= ~(SNDRV_PCM_INFO_FIFO_IN_FRAMES |
				  SNDRV_PCM_INFO_DRAIN_TRIGGER);
		if (!hw_support_mmap(substream))
			params->info &= ~(SNDRV_PCM_INFO_MMAP |
					  SNDRV_PCM_INFO_MMAP_VALID);
	}

	return 0;
}