#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct calldata {int dummy; } ;
struct audio_action {int set; int /*<<< orphan*/  type; int /*<<< orphan*/  timestamp; } ;
typedef  int /*<<< orphan*/  stack ;
struct TYPE_6__ {int /*<<< orphan*/  signals; } ;
struct TYPE_7__ {int user_muted; int /*<<< orphan*/  audio_actions_mutex; int /*<<< orphan*/  audio_actions; TYPE_1__ context; } ;
typedef  TYPE_2__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ACTION_MUTE ; 
 int /*<<< orphan*/  calldata_init_fixed (struct calldata*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  calldata_set_bool (struct calldata*,char*,int) ; 
 int /*<<< orphan*/  calldata_set_ptr (struct calldata*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct audio_action*) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  os_gettime_ns () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char*,struct calldata*) ; 

void obs_source_set_muted(obs_source_t *source, bool muted)
{
	struct calldata data;
	uint8_t stack[128];
	struct audio_action action = {.timestamp = os_gettime_ns(),
				      .type = AUDIO_ACTION_MUTE,
				      .set = muted};

	if (!obs_source_valid(source, "obs_source_set_muted"))
		return;

	source->user_muted = muted;

	calldata_init_fixed(&data, stack, sizeof(stack));
	calldata_set_ptr(&data, "source", source);
	calldata_set_bool(&data, "muted", muted);

	signal_handler_signal(source->context.signals, "mute", &data);

	pthread_mutex_lock(&source->audio_actions_mutex);
	da_push_back(source->audio_actions, &action);
	pthread_mutex_unlock(&source->audio_actions_mutex);
}