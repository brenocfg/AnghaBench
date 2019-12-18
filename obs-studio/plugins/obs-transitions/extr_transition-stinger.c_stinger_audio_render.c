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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct stinger_info {int /*<<< orphan*/  media_source; int /*<<< orphan*/  mix_b; int /*<<< orphan*/  mix_a; int /*<<< orphan*/  source; } ;
struct obs_source_audio_mix {TYPE_1__* output; } ;
struct TYPE_2__ {float** data; } ;

/* Variables and functions */
 int AUDIO_OUTPUT_FRAMES ; 
 size_t MAX_AUDIO_MIXES ; 
 int /*<<< orphan*/  obs_source_audio_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_get_audio_mix (int /*<<< orphan*/ ,struct obs_source_audio_mix*) ; 
 scalar_t__ obs_source_get_audio_timestamp (int /*<<< orphan*/ ) ; 
 int obs_transition_audio_render (int /*<<< orphan*/ ,scalar_t__*,struct obs_source_audio_mix*,int,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool stinger_audio_render(void *data, uint64_t *ts_out,
				 struct obs_source_audio_mix *audio,
				 uint32_t mixers, size_t channels,
				 size_t sample_rate)
{
	struct stinger_info *s = data;
	uint64_t ts = 0;

	if (!obs_source_audio_pending(s->media_source)) {
		ts = obs_source_get_audio_timestamp(s->media_source);
		if (!ts)
			return false;
	}

	bool success = obs_transition_audio_render(s->source, ts_out, audio,
						   mixers, channels,
						   sample_rate, s->mix_a,
						   s->mix_b);
	if (!ts)
		return success;

	if (!*ts_out || ts < *ts_out)
		*ts_out = ts;

	struct obs_source_audio_mix child_audio;
	obs_source_get_audio_mix(s->media_source, &child_audio);

	for (size_t mix = 0; mix < MAX_AUDIO_MIXES; mix++) {
		if ((mixers & (1 << mix)) == 0)
			continue;

		for (size_t ch = 0; ch < channels; ch++) {
			register float *out = audio->output[mix].data[ch];
			register float *in = child_audio.output[mix].data[ch];
			register float *end = in + AUDIO_OUTPUT_FRAMES;

			while (in < end)
				*(out++) += *(in++);
		}
	}

	return true;
}