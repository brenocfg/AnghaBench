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
struct alsa_data {char const* device; unsigned int rate; scalar_t__ handle; scalar_t__ active; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  _alsa_close (struct alsa_data*) ; 
 int /*<<< orphan*/  _alsa_try_open (struct alsa_data*) ; 
 int /*<<< orphan*/  bfree (char const*) ; 
 char const* bstrdup (char const*) ; 
 unsigned int obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

void alsa_update(void *vptr, obs_data_t *settings)
{
	struct alsa_data *data = vptr;
	const char *device;
	unsigned int rate;
	bool reset = false;

	device = obs_data_get_string(settings, "device_id");

	if (strcmp(device, "__custom__") == 0)
		device = obs_data_get_string(settings, "custom_pcm");

	if (strcmp(data->device, device) != 0) {
		bfree(data->device);
		data->device = bstrdup(device);
		reset = true;
	}

	rate = obs_data_get_int(settings, "rate");
	if (data->rate != rate) {
		data->rate = rate;
		reset = true;
	}

#if SHUTDOWN_ON_DEACTIVATE
	if (reset && data->handle)
		_alsa_close(data);

	if (data->active && !data->handle)
		_alsa_try_open(data);
#else
	if (reset) {
		if (data->handle)
			_alsa_close(data);
		_alsa_try_open(data);
	}
#endif
}