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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct audio_input {scalar_t__ resampler; } ;
struct audio_data {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  frames; int /*<<< orphan*/ ** data; } ;
typedef  int /*<<< orphan*/  output ;

/* Variables and functions */
 int MAX_AV_PLANES ; 
 int audio_resampler_resample (scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/  const* const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool resample_audio_output(struct audio_input *input,
				  struct audio_data *data)
{
	bool success = true;

	if (input->resampler) {
		uint8_t *output[MAX_AV_PLANES];
		uint32_t frames;
		uint64_t offset;

		memset(output, 0, sizeof(output));

		success = audio_resampler_resample(
			input->resampler, output, &frames, &offset,
			(const uint8_t *const *)data->data, data->frames);

		for (size_t i = 0; i < MAX_AV_PLANES; i++)
			data->data[i] = output[i];
		data->frames = frames;
		data->timestamp -= offset;
	}

	return success;
}