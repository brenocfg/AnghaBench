#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_4__ {scalar_t__ audio_render; } ;
struct obs_source {int audio_pending; int audio_ts; TYPE_1__* audio_input_buf; TYPE_2__ info; } ;
struct TYPE_3__ {size_t size; } ;

/* Variables and functions */
 size_t AUDIO_OUTPUT_FRAMES ; 
 size_t convert_time_to_frames (size_t,int) ; 

__attribute__((used)) static bool audio_buffer_insuffient(struct obs_source *source,
				    size_t sample_rate, uint64_t min_ts)
{
	size_t total_floats = AUDIO_OUTPUT_FRAMES;
	size_t size;

	if (source->info.audio_render || source->audio_pending ||
	    !source->audio_ts) {
		return false;
	}

	if (source->audio_ts != min_ts && source->audio_ts != (min_ts - 1)) {
		size_t start_point = convert_time_to_frames(
			sample_rate, source->audio_ts - min_ts);
		if (start_point >= AUDIO_OUTPUT_FRAMES)
			return false;

		total_floats -= start_point;
	}

	size = total_floats * sizeof(float);

	if (source->audio_input_buf[0].size < size) {
		source->audio_pending = true;
		return true;
	}

	return false;
}