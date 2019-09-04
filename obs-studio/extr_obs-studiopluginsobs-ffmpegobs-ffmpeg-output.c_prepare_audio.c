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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct ffmpeg_data {scalar_t__ start_timestamp; size_t audio_planes; int audio_size; scalar_t__ audio_samplerate; } ;
struct audio_data {scalar_t__ timestamp; int* data; scalar_t__ frames; } ;

/* Variables and functions */

__attribute__((used)) static bool prepare_audio(struct ffmpeg_data *data,
		const struct audio_data *frame, struct audio_data *output)
{
	*output = *frame;

	if (frame->timestamp < data->start_timestamp) {
		uint64_t duration = (uint64_t)frame->frames * 1000000000 /
			(uint64_t)data->audio_samplerate;
		uint64_t end_ts = (frame->timestamp + duration);
		uint64_t cutoff;

		if (end_ts <= data->start_timestamp)
			return false;

		cutoff = data->start_timestamp - frame->timestamp;
		output->timestamp += cutoff;

		cutoff = cutoff * (uint64_t)data->audio_samplerate /
			1000000000;

		for (size_t i = 0; i < data->audio_planes; i++)
			output->data[i] += data->audio_size * (uint32_t)cutoff;
		output->frames -= (uint32_t)cutoff;
	}

	return true;
}