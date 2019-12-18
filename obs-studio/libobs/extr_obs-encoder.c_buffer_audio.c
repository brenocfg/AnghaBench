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
typedef  unsigned long long uint64_t ;
struct obs_encoder {size_t blocksize; unsigned long long start_ts; TYPE_1__* paired_encoder; scalar_t__ samplerate; } ;
struct audio_data {size_t frames; unsigned long long timestamp; } ;
struct TYPE_2__ {unsigned long long start_ts; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_audio_name ; 
 size_t calc_offset_size (struct obs_encoder*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  clear_audio (struct obs_encoder*) ; 
 int /*<<< orphan*/  profile_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_back_audio (struct obs_encoder*,struct audio_data*,size_t,size_t) ; 
 int /*<<< orphan*/  start_from_buffer (struct obs_encoder*,unsigned long long) ; 

__attribute__((used)) static bool buffer_audio(struct obs_encoder *encoder, struct audio_data *data)
{
	profile_start(buffer_audio_name);

	size_t size = data->frames * encoder->blocksize;
	size_t offset_size = 0;
	bool success = true;

	if (!encoder->start_ts && encoder->paired_encoder) {
		uint64_t end_ts = data->timestamp;
		uint64_t v_start_ts = encoder->paired_encoder->start_ts;

		/* no video yet, so don't start audio */
		if (!v_start_ts) {
			success = false;
			goto fail;
		}

		/* audio starting point still not synced with video starting
		 * point, so don't start audio */
		end_ts += (uint64_t)data->frames * 1000000000ULL /
			  (uint64_t)encoder->samplerate;
		if (end_ts <= v_start_ts) {
			success = false;
			goto fail;
		}

		/* ready to start audio, truncate if necessary */
		if (data->timestamp < v_start_ts)
			offset_size = calc_offset_size(encoder, v_start_ts,
						       data->timestamp);
		if (data->timestamp <= v_start_ts)
			clear_audio(encoder);

		encoder->start_ts = v_start_ts;

		/* use currently buffered audio instead */
		if (v_start_ts < data->timestamp) {
			start_from_buffer(encoder, v_start_ts);
		}

	} else if (!encoder->start_ts && !encoder->paired_encoder) {
		encoder->start_ts = data->timestamp;
	}

fail:
	push_back_audio(encoder, data, size, offset_size);

	profile_end(buffer_audio_name);
	return success;
}