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
struct jack_data {int channels; int /*<<< orphan*/  jack_mutex; int /*<<< orphan*/ * jack_client; int /*<<< orphan*/ ** jack_ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  jack_client_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jack_port_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void deactivate_jack(struct jack_data *data)
{
	pthread_mutex_lock(&data->jack_mutex);

	if (data->jack_client) {
		if (data->jack_ports != NULL) {
			for (int i = 0; i < data->channels; ++i) {
				if (data->jack_ports[i] != NULL)
					jack_port_unregister(
						data->jack_client,
						data->jack_ports[i]);
			}
			bfree(data->jack_ports);
			data->jack_ports = NULL;
		}
		jack_client_close(data->jack_client);
		data->jack_client = NULL;
	}
	pthread_mutex_unlock(&data->jack_mutex);
}