#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct calldata {int dummy; } ;
struct audio_action {float vol; int /*<<< orphan*/  type; int /*<<< orphan*/  timestamp; } ;
typedef  int /*<<< orphan*/  stack ;
struct TYPE_7__ {int /*<<< orphan*/  private; int /*<<< orphan*/  signals; } ;
struct TYPE_8__ {float user_volume; int /*<<< orphan*/  audio_actions_mutex; int /*<<< orphan*/  audio_actions; TYPE_1__ context; } ;
typedef  TYPE_2__ obs_source_t ;
struct TYPE_9__ {int /*<<< orphan*/  signals; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ACTION_VOL ; 
 scalar_t__ calldata_float (struct calldata*,char*) ; 
 int /*<<< orphan*/  calldata_init_fixed (struct calldata*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  calldata_set_float (struct calldata*,char*,float) ; 
 int /*<<< orphan*/  calldata_set_ptr (struct calldata*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct audio_action*) ; 
 TYPE_5__* obs ; 
 scalar_t__ obs_source_valid (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  os_gettime_ns () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char*,struct calldata*) ; 

void obs_source_set_volume(obs_source_t *source, float volume)
{
	if (obs_source_valid(source, "obs_source_set_volume")) {
		struct audio_action action = {.timestamp = os_gettime_ns(),
					      .type = AUDIO_ACTION_VOL,
					      .vol = volume};

		struct calldata data;
		uint8_t stack[128];

		calldata_init_fixed(&data, stack, sizeof(stack));
		calldata_set_ptr(&data, "source", source);
		calldata_set_float(&data, "volume", volume);

		signal_handler_signal(source->context.signals, "volume", &data);
		if (!source->context.private)
			signal_handler_signal(obs->signals, "source_volume",
					      &data);

		volume = (float)calldata_float(&data, "volume");

		pthread_mutex_lock(&source->audio_actions_mutex);
		da_push_back(source->audio_actions, &action);
		pthread_mutex_unlock(&source->audio_actions_mutex);

		source->user_volume = volume;
	}
}