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
struct jack_data {int channels; int /*<<< orphan*/  jack_mutex; int /*<<< orphan*/ * jack_client; int /*<<< orphan*/ ** jack_ports; int /*<<< orphan*/  device; scalar_t__ start_jack_server; } ;
typedef  int /*<<< orphan*/  port_name ;
typedef  int /*<<< orphan*/  jack_port_t ;
typedef  int /*<<< orphan*/  jack_options_t ;
typedef  int int_fast32_t ;

/* Variables and functions */
 int /*<<< orphan*/  JACK_DEFAULT_AUDIO_TYPE ; 
 int /*<<< orphan*/  JackNoStartServer ; 
 int /*<<< orphan*/  JackNullOption ; 
 int /*<<< orphan*/  JackPortIsInput ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ bzalloc (int) ; 
 scalar_t__ jack_activate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jack_client_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jack_port_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jack_process_callback ; 
 scalar_t__ jack_set_process_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct jack_data*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

int_fast32_t jack_init(struct jack_data *data)
{
	pthread_mutex_lock(&data->jack_mutex);

	if (data->jack_client != NULL)
		goto good;

	jack_options_t jack_option =
		data->start_jack_server ? JackNullOption : JackNoStartServer;

	data->jack_client = jack_client_open(data->device, jack_option, 0);
	if (data->jack_client == NULL) {
		blog(LOG_ERROR,
		     "jack_client_open Error:"
		     "Could not create JACK client! %s",
		     data->device);
		goto error;
	}

	data->jack_ports =
		(jack_port_t **)bzalloc(sizeof(jack_port_t *) * data->channels);
	for (unsigned int i = 0; i < data->channels; ++i) {
		char port_name[10] = {'\0'};
		snprintf(port_name, sizeof(port_name), "in_%u", i + 1);

		data->jack_ports[i] = jack_port_register(
			data->jack_client, port_name, JACK_DEFAULT_AUDIO_TYPE,
			JackPortIsInput, 0);
		if (data->jack_ports[i] == NULL) {
			blog(LOG_ERROR,
			     "jack_port_register Error:"
			     "Could not create JACK port! %s",
			     port_name);
			goto error;
		}
	}

	if (jack_set_process_callback(data->jack_client, jack_process_callback,
				      data) != 0) {
		blog(LOG_ERROR, "jack_set_process_callback Error");
		goto error;
	}

	if (jack_activate(data->jack_client) != 0) {
		blog(LOG_ERROR, "jack_activate Error:"
				"Could not activate JACK client!");
		goto error;
	}

good:
	pthread_mutex_unlock(&data->jack_mutex);
	return 0;

error:
	pthread_mutex_unlock(&data->jack_mutex);
	return 1;
}