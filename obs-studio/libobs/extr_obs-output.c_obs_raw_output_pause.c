#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ts_start; } ;
struct TYPE_7__ {TYPE_2__ pause; } ;
typedef  TYPE_1__ obs_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  end_pause (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_closest_v_ts (TYPE_2__*) ; 
 int pause_can_start (TYPE_2__*) ; 
 int pause_can_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool obs_raw_output_pause(obs_output_t *output, bool pause)
{
	bool success;
	uint64_t closest_v_ts;

	pthread_mutex_lock(&output->pause.mutex);
	closest_v_ts = get_closest_v_ts(&output->pause);
	if (pause) {
		success = pause_can_start(&output->pause);
		if (success)
			output->pause.ts_start = closest_v_ts;
	} else {
		success = pause_can_stop(&output->pause);
		if (success)
			end_pause(&output->pause, closest_v_ts);
	}
	pthread_mutex_unlock(&output->pause.mutex);

	return success;
}