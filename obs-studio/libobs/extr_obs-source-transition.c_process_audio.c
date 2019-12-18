#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct obs_source_audio_mix {struct audio_output_data* output; } ;
struct audio_output_data {float** data; } ;
typedef  int /*<<< orphan*/  obs_transition_audio_mix_callback_t ;
struct TYPE_6__ {scalar_t__ audio_ts; int /*<<< orphan*/  audio_pending; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 size_t AUDIO_OUTPUT_FRAMES ; 
 size_t MAX_AUDIO_MIXES ; 
 int /*<<< orphan*/  mix_child (TYPE_1__*,float*,float*,size_t,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ns_to_audio_frames (size_t,scalar_t__) ; 
 int /*<<< orphan*/  obs_source_get_audio_mix (TYPE_1__*,struct obs_source_audio_mix*) ; 

__attribute__((used)) static void process_audio(obs_source_t *transition, obs_source_t *child,
			  struct obs_source_audio_mix *audio, uint64_t min_ts,
			  uint32_t mixers, size_t channels, size_t sample_rate,
			  obs_transition_audio_mix_callback_t mix)
{
	bool valid = child && !child->audio_pending;
	struct obs_source_audio_mix child_audio;
	uint64_t ts;
	size_t pos;

	if (!valid)
		return;

	ts = child->audio_ts;
	obs_source_get_audio_mix(child, &child_audio);
	pos = (size_t)ns_to_audio_frames(sample_rate, ts - min_ts);

	if (pos > AUDIO_OUTPUT_FRAMES)
		return;

	for (size_t mix_idx = 0; mix_idx < MAX_AUDIO_MIXES; mix_idx++) {
		struct audio_output_data *output = &audio->output[mix_idx];
		struct audio_output_data *input = &child_audio.output[mix_idx];

		if ((mixers & (1 << mix_idx)) == 0)
			continue;

		for (size_t ch = 0; ch < channels; ch++) {
			float *out = output->data[ch];
			float *in = input->data[ch];

			mix_child(transition, out + pos, in,
				  AUDIO_OUTPUT_FRAMES - pos, sample_rate, ts,
				  mix);
		}
	}
}