#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  signal_handler_t ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * source; } ;
typedef  TYPE_1__ obs_volmeter_t ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/ * obs_source_get_signal_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_remove_audio_capture_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler_disconnect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  volmeter_source_data_received ; 
 int /*<<< orphan*/  volmeter_source_destroyed ; 
 int /*<<< orphan*/  volmeter_source_volume_changed ; 

void obs_volmeter_detach_source(obs_volmeter_t *volmeter)
{
	signal_handler_t *sh;
	obs_source_t *source;

	if (!volmeter)
		return;

	pthread_mutex_lock(&volmeter->mutex);
	source = volmeter->source;
	volmeter->source = NULL;
	pthread_mutex_unlock(&volmeter->mutex);

	if (!source)
		return;

	sh = obs_source_get_signal_handler(source);
	signal_handler_disconnect(sh, "volume", volmeter_source_volume_changed,
				  volmeter);
	signal_handler_disconnect(sh, "destroy", volmeter_source_destroyed,
				  volmeter);
	obs_source_remove_audio_capture_callback(
		source, volmeter_source_data_received, volmeter);
}