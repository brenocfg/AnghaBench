#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  signal_handler_t ;
typedef  int /*<<< orphan*/  obs_source_t ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * source; } ;
typedef  TYPE_1__ obs_fader_t ;

/* Variables and functions */
 int /*<<< orphan*/  fader_source_destroyed ; 
 int /*<<< orphan*/  fader_source_volume_changed ; 
 int /*<<< orphan*/ * obs_source_get_signal_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler_disconnect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 

void obs_fader_detach_source(obs_fader_t *fader)
{
	signal_handler_t *sh;
	obs_source_t *source;

	if (!fader)
		return;

	pthread_mutex_lock(&fader->mutex);
	source = fader->source;
	fader->source = NULL;
	pthread_mutex_unlock(&fader->mutex);

	if (!source)
		return;

	sh = obs_source_get_signal_handler(source);
	signal_handler_disconnect(sh, "volume", fader_source_volume_changed,
				  fader);
	signal_handler_disconnect(sh, "destroy", fader_source_destroyed, fader);
}