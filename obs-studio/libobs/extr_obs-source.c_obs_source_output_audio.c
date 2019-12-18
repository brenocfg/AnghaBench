#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct obs_source_audio {int dummy; } ;
struct obs_audio_data {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  frames; int /*<<< orphan*/ * data; } ;
struct audio_data {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  frames; int /*<<< orphan*/ * data; } ;
struct TYPE_7__ {int /*<<< orphan*/  filter_mutex; int /*<<< orphan*/  audio_mutex; int /*<<< orphan*/  audio_data; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int MAX_AV_PLANES ; 
 struct obs_audio_data* filter_async_audio (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_ptr_valid (struct obs_source_audio const*,char*) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  process_audio (TYPE_1__*,struct obs_source_audio const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  source_output_audio_data (TYPE_1__*,struct audio_data*) ; 

void obs_source_output_audio(obs_source_t *source,
			     const struct obs_source_audio *audio)
{
	struct obs_audio_data *output;

	if (!obs_source_valid(source, "obs_source_output_audio"))
		return;
	if (!obs_ptr_valid(audio, "obs_source_output_audio"))
		return;

	process_audio(source, audio);

	pthread_mutex_lock(&source->filter_mutex);
	output = filter_async_audio(source, &source->audio_data);

	if (output) {
		struct audio_data data;

		for (int i = 0; i < MAX_AV_PLANES; i++)
			data.data[i] = output->data[i];

		data.frames = output->frames;
		data.timestamp = output->timestamp;

		pthread_mutex_lock(&source->audio_mutex);
		source_output_audio_data(source, &data);
		pthread_mutex_unlock(&source->audio_mutex);
	}

	pthread_mutex_unlock(&source->filter_mutex);
}