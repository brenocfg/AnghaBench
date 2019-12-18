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
struct obs_output {int /*<<< orphan*/  service; int /*<<< orphan*/  video; int /*<<< orphan*/  video_encoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  audio_valid (struct obs_output const*,int) ; 

__attribute__((used)) static bool can_begin_data_capture(const struct obs_output *output,
				   bool encoded, bool has_video, bool has_audio,
				   bool has_service)
{
	if (has_video) {
		if (encoded) {
			if (!output->video_encoder)
				return false;
		} else {
			if (!output->video)
				return false;
		}
	}

	if (has_audio) {
		if (!audio_valid(output, encoded)) {
			return false;
		}
	}

	if (has_service && !output->service)
		return false;

	return true;
}