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
struct obs_source {int user_push_to_talk_pressed; int /*<<< orphan*/  audio_actions_mutex; int /*<<< orphan*/  audio_actions; } ;
struct audio_action {int set; int /*<<< orphan*/  type; int /*<<< orphan*/  timestamp; } ;
typedef  int /*<<< orphan*/  obs_hotkey_t ;
typedef  int /*<<< orphan*/ * obs_hotkey_id ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ACTION_PTT ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct audio_action*) ; 
 int /*<<< orphan*/  os_gettime_ns () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void obs_source_hotkey_push_to_talk(void *data, obs_hotkey_id id,
					   obs_hotkey_t *key, bool pressed)
{
	struct audio_action action = {.timestamp = os_gettime_ns(),
				      .type = AUDIO_ACTION_PTT,
				      .set = pressed};

	UNUSED_PARAMETER(id);
	UNUSED_PARAMETER(key);

	struct obs_source *source = data;

	pthread_mutex_lock(&source->audio_actions_mutex);
	da_push_back(source->audio_actions, &action);
	pthread_mutex_unlock(&source->audio_actions_mutex);

	source->user_push_to_talk_pressed = pressed;
}