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
struct alsa_data {int /*<<< orphan*/  device; int /*<<< orphan*/  listen_thread; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  PTHREAD_CREATE_JOINABLE ; 
 scalar_t__ SND_PCM_STATE_PREPARED ; 
 int /*<<< orphan*/  SND_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  _alsa_close (struct alsa_data*) ; 
 int /*<<< orphan*/  _alsa_configure (struct alsa_data*) ; 
 int /*<<< orphan*/  _alsa_listen ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct alsa_data*) ; 
 int snd_pcm_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_start (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_strerror (int) ; 

bool _alsa_open(struct alsa_data *data)
{
	pthread_attr_t attr;
	int err;

	err = snd_pcm_open(&data->handle, data->device, SND_PCM_STREAM_CAPTURE,
			   0);
	if (err < 0) {
		blog(LOG_ERROR, "Failed to open '%s': %s", data->device,
		     snd_strerror(err));
		return false;
	}

	if (!_alsa_configure(data))
		goto cleanup;

	if (snd_pcm_state(data->handle) != SND_PCM_STATE_PREPARED) {
		blog(LOG_ERROR, "Device not prepared: '%s'", data->device);
		goto cleanup;
	}

	/* start listening */

	err = snd_pcm_start(data->handle);
	if (err < 0) {
		blog(LOG_ERROR, "Failed to start '%s': %s", data->device,
		     snd_strerror(err));
		goto cleanup;
	}

	/* create capture thread */

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	err = pthread_create(&data->listen_thread, &attr, _alsa_listen, data);
	if (err) {
		pthread_attr_destroy(&attr);
		blog(LOG_ERROR,
		     "Failed to create capture thread for device '%s'.",
		     data->device);
		goto cleanup;
	}

	pthread_attr_destroy(&attr);
	return true;

cleanup:
	_alsa_close(data);
	return false;
}