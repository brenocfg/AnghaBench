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
typedef  scalar_t__ uint32_t ;
struct noise_suppress_data {int suppress_level; size_t frames; size_t channels; void** segment_buffers; void** copy_buffers; scalar_t__* states; } ;
typedef  int /*<<< orphan*/  spx_int16_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_SUPPRESS_LEVEL ; 
 int /*<<< orphan*/  alloc_channel (struct noise_suppress_data*,scalar_t__,size_t,size_t) ; 
 size_t audio_output_get_channels (int /*<<< orphan*/ ) ; 
 scalar_t__ audio_output_get_sample_rate (int /*<<< orphan*/ ) ; 
 void* bmalloc (size_t) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_get_audio () ; 

__attribute__((used)) static void noise_suppress_update(void *data, obs_data_t *s)
{
	struct noise_suppress_data *ng = data;

	uint32_t sample_rate = audio_output_get_sample_rate(obs_get_audio());
	size_t channels = audio_output_get_channels(obs_get_audio());
	size_t frames = (size_t)sample_rate / 100;

	ng->suppress_level = (int)obs_data_get_int(s, S_SUPPRESS_LEVEL);

	/* Process 10 millisecond segments to keep latency low */
	ng->frames = frames;
	ng->channels = channels;

	/* Ignore if already allocated */
	if (ng->states[0])
		return;

	/* One speex state for each channel (limit 2) */
	ng->copy_buffers[0] = bmalloc(frames * channels * sizeof(float));
	ng->segment_buffers[0] =
		bmalloc(frames * channels * sizeof(spx_int16_t));
	for (size_t c = 1; c < channels; ++c) {
		ng->copy_buffers[c] = ng->copy_buffers[c - 1] + frames;
		ng->segment_buffers[c] = ng->segment_buffers[c - 1] + frames;
	}

	for (size_t i = 0; i < channels; i++)
		alloc_channel(ng, sample_rate, i, frames);
}