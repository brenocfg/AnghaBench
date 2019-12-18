#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct audio_action {scalar_t__ timestamp; } ;
struct TYPE_7__ {scalar_t__ num; struct audio_action* array; } ;
struct TYPE_8__ {scalar_t__ audio_ts; scalar_t__ audio_mixers; int /*<<< orphan*/ ** audio_output_buf; int /*<<< orphan*/  audio_actions_mutex; TYPE_1__ audio_actions; } ;
typedef  TYPE_2__ obs_source_t ;

/* Variables and functions */
 int AUDIO_OUTPUT_FRAMES ; 
 int MAX_AUDIO_CHANNELS ; 
 int MAX_AUDIO_MIXES ; 
 int /*<<< orphan*/  apply_audio_actions (TYPE_2__*,size_t,size_t) ; 
 scalar_t__ conv_frames_to_time (size_t,int) ; 
 float get_source_volume (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  multiply_output_audio (TYPE_2__*,size_t,size_t,float) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void apply_audio_volume(obs_source_t *source, uint32_t mixers,
			       size_t channels, size_t sample_rate)
{
	struct audio_action action;
	bool actions_pending;
	float vol;

	pthread_mutex_lock(&source->audio_actions_mutex);

	actions_pending = source->audio_actions.num > 0;
	if (actions_pending)
		action = source->audio_actions.array[0];

	pthread_mutex_unlock(&source->audio_actions_mutex);

	if (actions_pending) {
		uint64_t duration =
			conv_frames_to_time(sample_rate, AUDIO_OUTPUT_FRAMES);

		if (action.timestamp < (source->audio_ts + duration)) {
			apply_audio_actions(source, channels, sample_rate);
			return;
		}
	}

	vol = get_source_volume(source, source->audio_ts);
	if (vol == 1.0f)
		return;

	if (vol == 0.0f || mixers == 0) {
		memset(source->audio_output_buf[0][0], 0,
		       AUDIO_OUTPUT_FRAMES * sizeof(float) *
			       MAX_AUDIO_CHANNELS * MAX_AUDIO_MIXES);
		return;
	}

	for (size_t mix = 0; mix < MAX_AUDIO_MIXES; mix++) {
		uint32_t mix_and_val = (1 << mix);
		if ((source->audio_mixers & mix_and_val) != 0 &&
		    (mixers & mix_and_val) != 0)
			multiply_output_audio(source, mix, channels, vol);
	}
}