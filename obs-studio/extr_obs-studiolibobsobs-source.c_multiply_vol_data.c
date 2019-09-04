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
struct TYPE_3__ {float*** audio_output_buf; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int AUDIO_OUTPUT_FRAMES ; 

__attribute__((used)) static inline void multiply_vol_data(obs_source_t *source, size_t mix,
		size_t channels, float *vol_data)
{
	for (size_t ch = 0; ch < channels; ch++) {
		register float *out = source->audio_output_buf[mix][ch];
		register float *end = out + AUDIO_OUTPUT_FRAMES;
		register float *vol = vol_data;

		while (out < end)
			*(out++) *= *(vol++);
	}
}