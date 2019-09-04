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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  audio_mutex; int /*<<< orphan*/  push_to_talk_delay; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_source_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  source_signal_push_to_delay (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

void obs_source_set_push_to_talk_delay(obs_source_t *source, uint64_t delay)
{
	if (!obs_source_valid(source, "obs_source_set_push_to_talk_delay"))
		return;

	pthread_mutex_lock(&source->audio_mutex);
	source->push_to_talk_delay = delay;

	source_signal_push_to_delay(source, "push_to_talk_delay", delay);
	pthread_mutex_unlock(&source->audio_mutex);
}