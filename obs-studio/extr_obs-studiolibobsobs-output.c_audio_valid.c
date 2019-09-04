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
struct obs_output {int /*<<< orphan*/  audio; int /*<<< orphan*/ * audio_encoders; } ;

/* Variables and functions */
 size_t num_audio_mixes (struct obs_output const*) ; 

__attribute__((used)) static inline bool audio_valid(const struct obs_output *output, bool encoded)
{
	if (encoded) {
		size_t mix_count = num_audio_mixes(output);
		if (!mix_count)
			return false;

		for (size_t i = 0; i < mix_count; i++) {
			if (!output->audio_encoders[i]) {
				return false;
			}
		}
	} else {
		if (!output->audio)
			return false;
	}

	return true;
}