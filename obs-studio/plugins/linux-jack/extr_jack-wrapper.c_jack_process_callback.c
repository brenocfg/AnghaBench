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
struct obs_source_audio {scalar_t__ timestamp; int /*<<< orphan*/  frames; int /*<<< orphan*/ ** data; int /*<<< orphan*/  format; int /*<<< orphan*/  samples_per_sec; int /*<<< orphan*/  speakers; } ;
struct jack_data {unsigned int channels; int /*<<< orphan*/  jack_mutex; int /*<<< orphan*/  source; int /*<<< orphan*/  jack_client; int /*<<< orphan*/ * jack_ports; } ;
typedef  int /*<<< orphan*/  jack_nframes_t ;
typedef  int /*<<< orphan*/  jack_default_audio_sample_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_FORMAT_FLOAT_PLANAR ; 
 int /*<<< orphan*/  jack_channels_to_obs_speakers (unsigned int) ; 
 scalar_t__ jack_frames_to_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jack_get_sample_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ jack_port_get_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_output_audio (int /*<<< orphan*/ ,struct obs_source_audio*) ; 
 scalar_t__ os_gettime_ns () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int jack_process_callback(jack_nframes_t nframes, void *arg)
{
	struct jack_data *data = (struct jack_data *)arg;
	if (data == 0)
		return 0;

	pthread_mutex_lock(&data->jack_mutex);

	struct obs_source_audio out;
	out.speakers = jack_channels_to_obs_speakers(data->channels);
	out.samples_per_sec = jack_get_sample_rate(data->jack_client);
	/* format is always 32 bit float for jack */
	out.format = AUDIO_FORMAT_FLOAT_PLANAR;

	for (unsigned int i = 0; i < data->channels; ++i) {
		jack_default_audio_sample_t *jack_buffer =
			(jack_default_audio_sample_t *)jack_port_get_buffer(
				data->jack_ports[i], nframes);
		out.data[i] = (uint8_t *)jack_buffer;
	}

	out.frames = nframes;
	out.timestamp = os_gettime_ns() -
			jack_frames_to_time(data->jack_client, nframes);

	obs_source_output_audio(data->source, &out);
	pthread_mutex_unlock(&data->jack_mutex);
	return 0;
}