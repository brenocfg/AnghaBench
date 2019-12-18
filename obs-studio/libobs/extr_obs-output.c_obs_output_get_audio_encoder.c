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
struct TYPE_5__ {int flags; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** audio_encoders; TYPE_1__ info; } ;
typedef  TYPE_2__ obs_output_t ;
typedef  int /*<<< orphan*/  obs_encoder_t ;

/* Variables and functions */
 size_t MAX_AUDIO_MIXES ; 
 int OBS_OUTPUT_MULTI_TRACK ; 
 int /*<<< orphan*/  obs_output_valid (TYPE_2__ const*,char*) ; 

obs_encoder_t *obs_output_get_audio_encoder(const obs_output_t *output,
					    size_t idx)
{
	if (!obs_output_valid(output, "obs_output_get_audio_encoder"))
		return NULL;

	if ((output->info.flags & OBS_OUTPUT_MULTI_TRACK) != 0) {
		if (idx >= MAX_AUDIO_MIXES) {
			return NULL;
		}
	} else {
		if (idx > 0) {
			return NULL;
		}
	}

	return output->audio_encoders[idx];
}