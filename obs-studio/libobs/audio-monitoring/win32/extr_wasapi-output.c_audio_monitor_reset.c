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
struct audio_monitor {int /*<<< orphan*/ * source; int /*<<< orphan*/  playback_mutex; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  audio_monitor_free (struct audio_monitor*) ; 
 int audio_monitor_init (struct audio_monitor*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audio_monitor_init_final (struct audio_monitor*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void audio_monitor_reset(struct audio_monitor *monitor)
{
	struct audio_monitor new_monitor = {0};
	bool success;

	pthread_mutex_lock(&monitor->playback_mutex);
	success = audio_monitor_init(&new_monitor, monitor->source);
	pthread_mutex_unlock(&monitor->playback_mutex);

	if (success) {
		obs_source_t *source = monitor->source;
		audio_monitor_free(monitor);
		*monitor = new_monitor;
		audio_monitor_init_final(monitor);
	} else {
		audio_monitor_free(&new_monitor);
	}
}