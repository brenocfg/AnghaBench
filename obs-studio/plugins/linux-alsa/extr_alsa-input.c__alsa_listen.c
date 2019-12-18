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
struct obs_source_audio {int samples_per_sec; int frames; scalar_t__ timestamp; int /*<<< orphan*/  speakers; int /*<<< orphan*/  format; int /*<<< orphan*/ * data; } ;
struct alsa_data {int rate; scalar_t__ first_ts; int /*<<< orphan*/  source; int /*<<< orphan*/  handle; int /*<<< orphan*/  listen; int /*<<< orphan*/  period_size; int /*<<< orphan*/  buffer; int /*<<< orphan*/  channels; int /*<<< orphan*/  format; } ;
typedef  int snd_pcm_sframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int NSEC_PER_SEC ; 
 scalar_t__ STARTUP_TIMEOUT_NS ; 
 int /*<<< orphan*/  _alsa_channels_to_obs_speakers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _alsa_to_obs_audio_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  obs_source_output_audio (int /*<<< orphan*/ ,struct obs_source_audio*) ; 
 scalar_t__ os_atomic_load_bool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 scalar_t__ os_gettime_ns () ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 int snd_pcm_readi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_recover (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_wait (int /*<<< orphan*/ ,int) ; 

void *_alsa_listen(void *attr)
{
	struct alsa_data *data = attr;
	struct obs_source_audio out;

	blog(LOG_DEBUG, "Capture thread started.");

	out.data[0] = data->buffer;
	out.format = _alsa_to_obs_audio_format(data->format);
	out.speakers = _alsa_channels_to_obs_speakers(data->channels);
	out.samples_per_sec = data->rate;

	os_atomic_set_bool(&data->listen, true);

	do {
		snd_pcm_sframes_t frames = snd_pcm_readi(
			data->handle, data->buffer, data->period_size);

		if (!os_atomic_load_bool(&data->listen))
			break;

		if (frames <= 0) {
			frames = snd_pcm_recover(data->handle, frames, 0);
			if (frames <= 0) {
				snd_pcm_wait(data->handle, 100);
				continue;
			}
		}

		out.frames = frames;
		out.timestamp = os_gettime_ns() -
				((frames * NSEC_PER_SEC) / data->rate);

		if (!data->first_ts)
			data->first_ts = out.timestamp + STARTUP_TIMEOUT_NS;

		if (out.timestamp > data->first_ts)
			obs_source_output_audio(data->source, &out);
	} while (os_atomic_load_bool(&data->listen));

	blog(LOG_DEBUG, "Capture thread is about to exit.");

	pthread_exit(NULL);
	return NULL;
}