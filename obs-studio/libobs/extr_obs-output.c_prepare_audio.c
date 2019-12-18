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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__ last_video_ts; int /*<<< orphan*/  mutex; } ;
struct obs_output {scalar_t__ video_start_ts; size_t planes; int audio_size; scalar_t__ sample_rate; TYPE_1__ pause; } ;
struct audio_data {scalar_t__ timestamp; int* data; scalar_t__ frames; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool prepare_audio(struct obs_output *output,
			  const struct audio_data *old, struct audio_data *new)
{
	if (!output->video_start_ts) {
		pthread_mutex_lock(&output->pause.mutex);
		output->video_start_ts = output->pause.last_video_ts;
		pthread_mutex_unlock(&output->pause.mutex);
	}

	if (!output->video_start_ts)
		return false;

	/* ------------------ */

	*new = *old;

	if (old->timestamp < output->video_start_ts) {
		uint64_t duration = (uint64_t)old->frames * 1000000000 /
				    (uint64_t)output->sample_rate;
		uint64_t end_ts = (old->timestamp + duration);
		uint64_t cutoff;

		if (end_ts <= output->video_start_ts)
			return false;

		cutoff = output->video_start_ts - old->timestamp;
		new->timestamp += cutoff;

		cutoff = cutoff * (uint64_t)output->sample_rate / 1000000000;

		for (size_t i = 0; i < output->planes; i++)
			new->data[i] += output->audio_size *(uint32_t)cutoff;
		new->frames -= (uint32_t)cutoff;
	}

	return true;
}