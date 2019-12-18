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
struct obs_source_audio {size_t frames; scalar_t__ timestamp; int /*<<< orphan*/  samples_per_sec; int /*<<< orphan*/ ** data; int /*<<< orphan*/  format; int /*<<< orphan*/  speakers; } ;
typedef  int /*<<< orphan*/  pa_stream ;
struct TYPE_2__ {size_t bytes_per_frame; scalar_t__ first_ts; int /*<<< orphan*/  stream; int /*<<< orphan*/  frames; int /*<<< orphan*/  packets; int /*<<< orphan*/  source; int /*<<< orphan*/  format; int /*<<< orphan*/  samples_per_sec; int /*<<< orphan*/  speakers; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  PULSE_DATA (void*) ; 
 scalar_t__ STARTUP_TIMEOUT_NS ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (size_t) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,unsigned int) ; 
 TYPE_1__* data ; 
 scalar_t__ get_sample_time (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_output_audio (int /*<<< orphan*/ ,struct obs_source_audio*) ; 
 int /*<<< orphan*/  pa_stream_drop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_stream_peek (int /*<<< orphan*/ ,void const**,size_t*) ; 
 int /*<<< orphan*/  pulse_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pulse_to_obs_audio_format (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pulse_stream_read(pa_stream *p, size_t nbytes, void *userdata)
{
	UNUSED_PARAMETER(p);
	UNUSED_PARAMETER(nbytes);
	PULSE_DATA(userdata);

	const void *frames;
	size_t bytes;

	if (!data->stream)
		goto exit;

	pa_stream_peek(data->stream, &frames, &bytes);

	// check if we got data
	if (!bytes)
		goto exit;

	if (!frames) {
		blog(LOG_ERROR, "Got audio hole of %u bytes",
		     (unsigned int)bytes);
		pa_stream_drop(data->stream);
		goto exit;
	}

	struct obs_source_audio out;
	out.speakers = data->speakers;
	out.samples_per_sec = data->samples_per_sec;
	out.format = pulse_to_obs_audio_format(data->format);
	out.data[0] = (uint8_t *)frames;
	out.frames = bytes / data->bytes_per_frame;
	out.timestamp = get_sample_time(out.frames, out.samples_per_sec);

	if (!data->first_ts)
		data->first_ts = out.timestamp + STARTUP_TIMEOUT_NS;

	if (out.timestamp > data->first_ts)
		obs_source_output_audio(data->source, &out);

	data->packets++;
	data->frames += out.frames;

	pa_stream_drop(data->stream);
exit:
	pulse_signal(0);
}