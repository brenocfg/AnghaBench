#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ts_info {scalar_t__ start; scalar_t__ end; } ;
struct audio_output_data {float** data; } ;
struct TYPE_3__ {scalar_t__ audio_ts; float*** audio_output_buf; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 size_t AUDIO_OUTPUT_FRAMES ; 
 size_t MAX_AUDIO_MIXES ; 
 size_t convert_time_to_frames (size_t,scalar_t__) ; 

__attribute__((used)) static inline void mix_audio(struct audio_output_data *mixes,
			     obs_source_t *source, size_t channels,
			     size_t sample_rate, struct ts_info *ts)
{
	size_t total_floats = AUDIO_OUTPUT_FRAMES;
	size_t start_point = 0;

	if (source->audio_ts < ts->start || ts->end <= source->audio_ts)
		return;

	if (source->audio_ts != ts->start) {
		start_point = convert_time_to_frames(
			sample_rate, source->audio_ts - ts->start);
		if (start_point == AUDIO_OUTPUT_FRAMES)
			return;

		total_floats -= start_point;
	}

	for (size_t mix_idx = 0; mix_idx < MAX_AUDIO_MIXES; mix_idx++) {
		for (size_t ch = 0; ch < channels; ch++) {
			register float *mix = mixes[mix_idx].data[ch];
			register float *aud =
				source->audio_output_buf[mix_idx][ch];
			register float *end;

			mix += start_point;
			end = aud + total_floats;

			while (aud < end)
				*(mix++) += *(aud++);
		}
	}
}