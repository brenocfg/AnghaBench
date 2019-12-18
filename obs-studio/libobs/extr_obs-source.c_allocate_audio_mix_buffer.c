#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct obs_source {float** audio_mix_buf; } ;

/* Variables and functions */
 int AUDIO_OUTPUT_FRAMES ; 
 int MAX_AUDIO_CHANNELS ; 
 float* bzalloc (size_t) ; 

__attribute__((used)) static void allocate_audio_mix_buffer(struct obs_source *source)
{
	size_t size = sizeof(float) * AUDIO_OUTPUT_FRAMES * MAX_AUDIO_CHANNELS;
	float *ptr = bzalloc(size);

	for (size_t i = 0; i < MAX_AUDIO_CHANNELS; i++) {
		source->audio_mix_buf[i] = ptr + AUDIO_OUTPUT_FRAMES * i;
	}
}