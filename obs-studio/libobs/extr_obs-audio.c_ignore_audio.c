#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
struct TYPE_4__ {unsigned long long audio_ts; scalar_t__ last_audio_input_buf_size; TYPE_3__* audio_input_buf; } ;
typedef  TYPE_1__ obs_source_t ;
struct TYPE_5__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  circlebuf_pop_front (TYPE_3__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ignore_audio(obs_source_t *source, size_t channels,
			 size_t sample_rate)
{
	size_t num_floats = source->audio_input_buf[0].size / sizeof(float);

	if (num_floats) {
		for (size_t ch = 0; ch < channels; ch++)
			circlebuf_pop_front(&source->audio_input_buf[ch], NULL,
					    source->audio_input_buf[ch].size);

		source->last_audio_input_buf_size = 0;
		source->audio_ts += (uint64_t)num_floats * 1000000000ULL /
				    (uint64_t)sample_rate;
	}
}