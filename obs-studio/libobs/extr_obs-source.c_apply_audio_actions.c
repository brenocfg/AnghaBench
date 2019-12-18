#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct audio_action {scalar_t__ timestamp; } ;
struct TYPE_8__ {size_t num; struct audio_action* array; } ;
struct TYPE_7__ {scalar_t__ audio_ts; int audio_mixers; int /*<<< orphan*/  audio_actions_mutex; TYPE_4__ audio_actions; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int AUDIO_OUTPUT_FRAMES ; 
 size_t MAX_AUDIO_MIXES ; 
 int /*<<< orphan*/  apply_audio_action (TYPE_1__*,struct audio_action*) ; 
 size_t conv_time_to_frames (size_t,scalar_t__) ; 
 int /*<<< orphan*/  da_erase (TYPE_4__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (float*) ; 
 float get_source_volume (TYPE_1__*,scalar_t__) ; 
 float* malloc (int) ; 
 int /*<<< orphan*/  multiply_vol_data (TYPE_1__*,size_t,size_t,float*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void apply_audio_actions(obs_source_t *source, size_t channels,
				size_t sample_rate)
{
	float *vol_data = malloc(sizeof(float) * AUDIO_OUTPUT_FRAMES);
	float cur_vol = get_source_volume(source, source->audio_ts);
	size_t frame_num = 0;

	pthread_mutex_lock(&source->audio_actions_mutex);

	for (size_t i = 0; i < source->audio_actions.num; i++) {
		struct audio_action action = source->audio_actions.array[i];
		uint64_t timestamp = action.timestamp;
		size_t new_frame_num;

		if (timestamp < source->audio_ts)
			timestamp = source->audio_ts;

		new_frame_num = conv_time_to_frames(
			sample_rate, timestamp - source->audio_ts);

		if (new_frame_num >= AUDIO_OUTPUT_FRAMES)
			break;

		da_erase(source->audio_actions, i--);

		apply_audio_action(source, &action);

		if (new_frame_num > frame_num) {
			for (; frame_num < new_frame_num; frame_num++)
				vol_data[frame_num] = cur_vol;
		}

		cur_vol = get_source_volume(source, timestamp);
	}

	for (; frame_num < AUDIO_OUTPUT_FRAMES; frame_num++)
		vol_data[frame_num] = cur_vol;

	pthread_mutex_unlock(&source->audio_actions_mutex);

	for (size_t mix = 0; mix < MAX_AUDIO_MIXES; mix++) {
		if ((source->audio_mixers & (1 << mix)) != 0)
			multiply_vol_data(source, mix, channels, vol_data);
	}

	free(vol_data);
}