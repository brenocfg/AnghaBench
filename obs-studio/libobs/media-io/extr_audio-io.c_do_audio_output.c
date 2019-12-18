#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct audio_output {size_t planes; int /*<<< orphan*/  input_mutex; struct audio_mix* mixes; } ;
struct TYPE_2__ {size_t num; struct audio_input* array; } ;
struct audio_mix {scalar_t__* buffer; TYPE_1__ inputs; } ;
struct audio_input {int /*<<< orphan*/  param; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,size_t,struct audio_data*) ;} ;
struct audio_data {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  frames; int /*<<< orphan*/ ** data; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ resample_audio_output (struct audio_input*,struct audio_data*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,size_t,struct audio_data*) ; 

__attribute__((used)) static inline void do_audio_output(struct audio_output *audio, size_t mix_idx,
				   uint64_t timestamp, uint32_t frames)
{
	struct audio_mix *mix = &audio->mixes[mix_idx];
	struct audio_data data;

	pthread_mutex_lock(&audio->input_mutex);

	for (size_t i = mix->inputs.num; i > 0; i--) {
		struct audio_input *input = mix->inputs.array + (i - 1);

		for (size_t i = 0; i < audio->planes; i++)
			data.data[i] = (uint8_t *)mix->buffer[i];
		data.frames = frames;
		data.timestamp = timestamp;

		if (resample_audio_output(input, &data))
			input->callback(input->param, mix_idx, &data);
	}

	pthread_mutex_unlock(&audio->input_mutex);
}