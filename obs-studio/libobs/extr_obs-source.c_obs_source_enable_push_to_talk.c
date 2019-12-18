#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int push_to_talk_enabled; int /*<<< orphan*/  audio_mutex; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int OBS_SOURCE_AUDIO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  obs_source_get_name (TYPE_1__*) ; 
 int obs_source_get_output_flags (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  source_signal_push_to_changed (TYPE_1__*,char*,int) ; 

void obs_source_enable_push_to_talk(obs_source_t *source, bool enabled)
{
	if (!obs_source_valid(source, "obs_source_enable_push_to_talk"))
		return;

	pthread_mutex_lock(&source->audio_mutex);
	bool changed = source->push_to_talk_enabled != enabled;
	if (obs_source_get_output_flags(source) & OBS_SOURCE_AUDIO && changed)
		blog(LOG_INFO, "source '%s' %s push-to-talk",
		     obs_source_get_name(source),
		     enabled ? "enabled" : "disabled");

	source->push_to_talk_enabled = enabled;

	if (changed)
		source_signal_push_to_changed(source, "push_to_talk_changed",
					      enabled);
	pthread_mutex_unlock(&source->audio_mutex);
}