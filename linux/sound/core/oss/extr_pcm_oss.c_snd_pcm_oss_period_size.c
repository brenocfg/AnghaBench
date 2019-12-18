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
struct TYPE_4__ {int period_size; int periods; } ;
struct TYPE_5__ {TYPE_1__ setup; } ;
struct snd_pcm_substream {TYPE_2__ oss; int /*<<< orphan*/  mmap_count; struct snd_pcm_runtime* runtime; } ;
struct TYPE_6__ {size_t mmap_bytes; int fragshift; int subdivision; size_t maxfrags; size_t period_bytes; int period_frames; size_t periods; } ;
struct snd_pcm_runtime {TYPE_3__ oss; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_SIZE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 size_t rounddown_pow_of_two (size_t) ; 
 size_t roundup_pow_of_two (size_t) ; 
 int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 
 size_t snd_pcm_hw_param_value_max (struct snd_pcm_hw_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t snd_pcm_hw_param_value_min (struct snd_pcm_hw_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t snd_pcm_plug_client_size (struct snd_pcm_substream*,size_t) ; 

__attribute__((used)) static int snd_pcm_oss_period_size(struct snd_pcm_substream *substream, 
				   struct snd_pcm_hw_params *oss_params,
				   struct snd_pcm_hw_params *slave_params)
{
	size_t s;
	size_t oss_buffer_size, oss_period_size, oss_periods;
	size_t min_period_size, max_period_size;
	struct snd_pcm_runtime *runtime = substream->runtime;
	size_t oss_frame_size;

	oss_frame_size = snd_pcm_format_physical_width(params_format(oss_params)) *
			 params_channels(oss_params) / 8;

	oss_buffer_size = snd_pcm_plug_client_size(substream,
						   snd_pcm_hw_param_value_max(slave_params, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, NULL)) * oss_frame_size;
	oss_buffer_size = rounddown_pow_of_two(oss_buffer_size);
	if (atomic_read(&substream->mmap_count)) {
		if (oss_buffer_size > runtime->oss.mmap_bytes)
			oss_buffer_size = runtime->oss.mmap_bytes;
	}

	if (substream->oss.setup.period_size > 16)
		oss_period_size = substream->oss.setup.period_size;
	else if (runtime->oss.fragshift) {
		oss_period_size = 1 << runtime->oss.fragshift;
		if (oss_period_size > oss_buffer_size / 2)
			oss_period_size = oss_buffer_size / 2;
	} else {
		int sd;
		size_t bytes_per_sec = params_rate(oss_params) * snd_pcm_format_physical_width(params_format(oss_params)) * params_channels(oss_params) / 8;

		oss_period_size = oss_buffer_size;
		do {
			oss_period_size /= 2;
		} while (oss_period_size > bytes_per_sec);
		if (runtime->oss.subdivision == 0) {
			sd = 4;
			if (oss_period_size / sd > 4096)
				sd *= 2;
			if (oss_period_size / sd < 4096)
				sd = 1;
		} else
			sd = runtime->oss.subdivision;
		oss_period_size /= sd;
		if (oss_period_size < 16)
			oss_period_size = 16;
	}

	min_period_size = snd_pcm_plug_client_size(substream,
						   snd_pcm_hw_param_value_min(slave_params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, NULL));
	min_period_size *= oss_frame_size;
	min_period_size = roundup_pow_of_two(min_period_size);
	if (oss_period_size < min_period_size)
		oss_period_size = min_period_size;

	max_period_size = snd_pcm_plug_client_size(substream,
						   snd_pcm_hw_param_value_max(slave_params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, NULL));
	max_period_size *= oss_frame_size;
	max_period_size = rounddown_pow_of_two(max_period_size);
	if (oss_period_size > max_period_size)
		oss_period_size = max_period_size;

	oss_periods = oss_buffer_size / oss_period_size;

	if (substream->oss.setup.periods > 1)
		oss_periods = substream->oss.setup.periods;

	s = snd_pcm_hw_param_value_max(slave_params, SNDRV_PCM_HW_PARAM_PERIODS, NULL);
	if (runtime->oss.maxfrags && s > runtime->oss.maxfrags)
		s = runtime->oss.maxfrags;
	if (oss_periods > s)
		oss_periods = s;

	s = snd_pcm_hw_param_value_min(slave_params, SNDRV_PCM_HW_PARAM_PERIODS, NULL);
	if (s < 2)
		s = 2;
	if (oss_periods < s)
		oss_periods = s;

	while (oss_period_size * oss_periods > oss_buffer_size)
		oss_period_size /= 2;

	if (oss_period_size < 16)
		return -EINVAL;
	runtime->oss.period_bytes = oss_period_size;
	runtime->oss.period_frames = 1;
	runtime->oss.periods = oss_periods;
	return 0;
}