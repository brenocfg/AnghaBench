#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct audio_monitor {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  monitoring_mutex; int /*<<< orphan*/  monitors; } ;
struct TYPE_4__ {TYPE_1__ audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  audio_monitor_free (struct audio_monitor*) ; 
 int /*<<< orphan*/  bfree (struct audio_monitor*) ; 
 int /*<<< orphan*/  da_erase_item (int /*<<< orphan*/ ,struct audio_monitor**) ; 
 TYPE_2__* obs ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void audio_monitor_destroy(struct audio_monitor *monitor)
{
	if (monitor) {
		audio_monitor_free(monitor);

		pthread_mutex_lock(&obs->audio.monitoring_mutex);
		da_erase_item(obs->audio.monitors, &monitor);
		pthread_mutex_unlock(&obs->audio.monitoring_mutex);

		bfree(monitor);
	}
}