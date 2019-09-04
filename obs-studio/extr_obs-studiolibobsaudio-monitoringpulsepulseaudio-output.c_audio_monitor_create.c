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
struct audio_monitor {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_source_t ;
typedef  int /*<<< orphan*/  monitor ;
struct TYPE_3__ {int /*<<< orphan*/  monitoring_mutex; int /*<<< orphan*/  monitors; } ;
struct TYPE_4__ {TYPE_1__ audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  audio_monitor_free (struct audio_monitor*) ; 
 int /*<<< orphan*/  audio_monitor_init (struct audio_monitor*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audio_monitor_init_final (struct audio_monitor*) ; 
 struct audio_monitor* bmemdup (struct audio_monitor*,int) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct audio_monitor**) ; 
 TYPE_2__* obs ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

struct audio_monitor *audio_monitor_create(obs_source_t *source)
{
	struct audio_monitor monitor = {0};
	struct audio_monitor *out;

	if (!audio_monitor_init(&monitor, source))
		goto fail;

	out = bmemdup(&monitor, sizeof(monitor));

	pthread_mutex_lock(&obs->audio.monitoring_mutex);
	da_push_back(obs->audio.monitors, &out);
	pthread_mutex_unlock(&obs->audio.monitoring_mutex);

	audio_monitor_init_final(out);
	return out;

fail:
	audio_monitor_free(&monitor);
	return NULL;
}