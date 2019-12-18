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
struct jack_data {int start_jack_server; int channels; scalar_t__ device; int /*<<< orphan*/  source; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (scalar_t__) ; 
 scalar_t__ bstrdup (char const*) ; 
 int /*<<< orphan*/  deactivate_jack (struct jack_data*) ; 
 scalar_t__ jack_init (struct jack_data*) ; 
 int obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 int obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 char* obs_source_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static void jack_update(void *vptr, obs_data_t *settings)
{
	struct jack_data *data = (struct jack_data *)vptr;
	if (!data)
		return;

	const char *new_device;
	bool settings_changed = false;
	bool new_jack_start_server = obs_data_get_bool(settings, "startjack");
	int new_channel_count = obs_data_get_int(settings, "channels");

	if (new_jack_start_server != data->start_jack_server) {
		data->start_jack_server = new_jack_start_server;
		settings_changed = true;
	}

	if (new_channel_count != data->channels)
		/*
		 * keep "old" channel count  for now,
		 * we need to destroy the correct number of channels
		 */
		settings_changed = true;

	new_device = obs_source_get_name(data->source);
	if (!data->device || strcmp(data->device, new_device) != 0) {
		if (data->device)
			bfree(data->device);
		data->device = bstrdup(new_device);
		settings_changed = true;
	}

	if (settings_changed) {
		deactivate_jack(data);

		data->channels = new_channel_count;

		if (jack_init(data) != 0) {
			deactivate_jack(data);
		}
	}
}