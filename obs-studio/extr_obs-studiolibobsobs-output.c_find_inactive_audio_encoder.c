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
struct obs_encoder {int /*<<< orphan*/  paired_encoder; int /*<<< orphan*/  active; } ;
struct TYPE_3__ {struct obs_encoder** audio_encoders; } ;
typedef  TYPE_1__ obs_output_t ;
typedef  struct obs_encoder obs_encoder_t ;

/* Variables and functions */

__attribute__((used)) static inline obs_encoder_t *find_inactive_audio_encoder(obs_output_t *output,
		size_t num_mixes)
{
	for (size_t i = 0; i < num_mixes; i++) {
		struct obs_encoder *audio = output->audio_encoders[i];

		if (!audio->active && !audio->paired_encoder)
			return audio;
	}

	return NULL;
}