#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct pulse_data {scalar_t__ format; int /*<<< orphan*/  device; int /*<<< orphan*/  stream; int /*<<< orphan*/  source; int /*<<< orphan*/  speakers; int /*<<< orphan*/  bytes_per_frame; int /*<<< orphan*/  channels; int /*<<< orphan*/  samples_per_sec; } ;
typedef  int /*<<< orphan*/  pa_stream_flags_t ;
struct TYPE_8__ {scalar_t__ format; int /*<<< orphan*/  channels; int /*<<< orphan*/  rate; } ;
typedef  TYPE_1__ pa_sample_spec ;
typedef  int /*<<< orphan*/  pa_channel_map ;
struct TYPE_9__ {void* tlength; void* prebuf; void* minreq; void* maxlength; int /*<<< orphan*/  fragsize; } ;
typedef  TYPE_2__ pa_buffer_attr ;
typedef  int int_fast32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 scalar_t__ PA_SAMPLE_INVALID ; 
 int /*<<< orphan*/  PA_STREAM_ADJUST_LATENCY ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  obs_source_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_frame_size (TYPE_1__*) ; 
 int /*<<< orphan*/  pa_sample_spec_valid (TYPE_1__*) ; 
 int pa_stream_connect_record (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_stream_set_read_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pa_usec_to_bytes (int,TYPE_1__*) ; 
 int /*<<< orphan*/  pulse_channel_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pulse_channels_to_obs_speakers (int /*<<< orphan*/ ) ; 
 scalar_t__ pulse_get_server_info (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pulse_get_source_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pulse_lock () ; 
 int /*<<< orphan*/  pulse_server_info ; 
 int /*<<< orphan*/  pulse_source_info ; 
 int /*<<< orphan*/  pulse_stop_recording (struct pulse_data*) ; 
 int /*<<< orphan*/  pulse_stream_new (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pulse_stream_read ; 
 int /*<<< orphan*/  pulse_unlock () ; 

__attribute__((used)) static int_fast32_t pulse_start_recording(struct pulse_data *data)
{
	if (pulse_get_server_info(pulse_server_info, (void *)data) < 0) {
		blog(LOG_ERROR, "Unable to get server info !");
		return -1;
	}

	if (pulse_get_source_info(pulse_source_info, data->device,
				  (void *)data) < 0) {
		blog(LOG_ERROR, "Unable to get source info !");
		return -1;
	}
	if (data->format == PA_SAMPLE_INVALID) {
		blog(LOG_ERROR,
		     "An error occurred while getting the source info!");
		return -1;
	}

	pa_sample_spec spec;
	spec.format = data->format;
	spec.rate = data->samples_per_sec;
	spec.channels = data->channels;

	if (!pa_sample_spec_valid(&spec)) {
		blog(LOG_ERROR, "Sample spec is not valid");
		return -1;
	}

	data->speakers = pulse_channels_to_obs_speakers(spec.channels);
	data->bytes_per_frame = pa_frame_size(&spec);

	pa_channel_map channel_map = pulse_channel_map(data->speakers);

	data->stream = pulse_stream_new(obs_source_get_name(data->source),
					&spec, &channel_map);
	if (!data->stream) {
		blog(LOG_ERROR, "Unable to create stream");
		return -1;
	}

	pulse_lock();
	pa_stream_set_read_callback(data->stream, pulse_stream_read,
				    (void *)data);
	pulse_unlock();

	pa_buffer_attr attr;
	attr.fragsize = pa_usec_to_bytes(25000, &spec);
	attr.maxlength = (uint32_t)-1;
	attr.minreq = (uint32_t)-1;
	attr.prebuf = (uint32_t)-1;
	attr.tlength = (uint32_t)-1;

	pa_stream_flags_t flags = PA_STREAM_ADJUST_LATENCY;

	pulse_lock();
	int_fast32_t ret = pa_stream_connect_record(data->stream, data->device,
						    &attr, flags);
	pulse_unlock();
	if (ret < 0) {
		pulse_stop_recording(data);
		blog(LOG_ERROR, "Unable to connect to stream");
		return -1;
	}

	blog(LOG_INFO, "Started recording from '%s'", data->device);
	return 0;
}