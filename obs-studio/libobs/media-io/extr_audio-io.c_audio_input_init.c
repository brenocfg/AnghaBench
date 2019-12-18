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
struct resample_info {scalar_t__ format; scalar_t__ samples_per_sec; scalar_t__ speakers; } ;
struct TYPE_3__ {scalar_t__ format; scalar_t__ samples_per_sec; scalar_t__ speakers; } ;
struct audio_output {TYPE_1__ info; } ;
struct TYPE_4__ {scalar_t__ format; scalar_t__ samples_per_sec; scalar_t__ speakers; } ;
struct audio_input {int /*<<< orphan*/ * resampler; TYPE_2__ conversion; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/ * audio_resampler_create (struct resample_info*,struct resample_info*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline bool audio_input_init(struct audio_input *input,
				    struct audio_output *audio)
{
	if (input->conversion.format != audio->info.format ||
	    input->conversion.samples_per_sec != audio->info.samples_per_sec ||
	    input->conversion.speakers != audio->info.speakers) {
		struct resample_info from = {
			.format = audio->info.format,
			.samples_per_sec = audio->info.samples_per_sec,
			.speakers = audio->info.speakers};

		struct resample_info to = {
			.format = input->conversion.format,
			.samples_per_sec = input->conversion.samples_per_sec,
			.speakers = input->conversion.speakers};

		input->resampler = audio_resampler_create(&to, &from);
		if (!input->resampler) {
			blog(LOG_ERROR, "audio_input_init: Failed to "
					"create resampler");
			return false;
		}
	} else {
		input->resampler = NULL;
	}

	return true;
}