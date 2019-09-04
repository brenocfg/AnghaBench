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
 size_t AUDIO_OUTPUT_FRAMES ; 

__attribute__((used)) static inline void multiply_output_audio(obs_source_t *source, size_t mix,
		size_t channels, float vol)
{
	register float *out = source->audio_output_buf[mix][0];
	register float *end = out + AUDIO_OUTPUT_FRAMES * channels;

	while (out < end)
		*(out++) *= vol;
}