#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct obs_source_audio_mix {TYPE_1__* output; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** audio_output_buf; } ;
typedef  TYPE_2__ obs_source_t ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 size_t MAX_AUDIO_CHANNELS ; 
 size_t MAX_AUDIO_MIXES ; 
 int /*<<< orphan*/  obs_ptr_valid (struct obs_source_audio_mix*,char*) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_2__ const*,char*) ; 

void obs_source_get_audio_mix(const obs_source_t *source,
			      struct obs_source_audio_mix *audio)
{
	if (!obs_source_valid(source, "obs_source_get_audio_mix"))
		return;
	if (!obs_ptr_valid(audio, "audio"))
		return;

	for (size_t mix = 0; mix < MAX_AUDIO_MIXES; mix++) {
		for (size_t ch = 0; ch < MAX_AUDIO_CHANNELS; ch++) {
			audio->output[mix].data[ch] =
				source->audio_output_buf[mix][ch];
		}
	}
}