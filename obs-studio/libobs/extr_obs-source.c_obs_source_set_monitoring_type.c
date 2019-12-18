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
struct TYPE_5__ {int monitoring_type; int /*<<< orphan*/ * monitor; } ;
typedef  TYPE_1__ obs_source_t ;
typedef  enum obs_monitoring_type { ____Placeholder_obs_monitoring_type } obs_monitoring_type ;

/* Variables and functions */
 scalar_t__ OBS_MONITORING_TYPE_NONE ; 
 int /*<<< orphan*/ * audio_monitor_create (TYPE_1__*) ; 
 int /*<<< orphan*/  audio_monitor_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_1__*,char*) ; 

void obs_source_set_monitoring_type(obs_source_t *source,
				    enum obs_monitoring_type type)
{
	bool was_on;
	bool now_on;

	if (!obs_source_valid(source, "obs_source_set_monitoring_type"))
		return;
	if (source->monitoring_type == type)
		return;

	was_on = source->monitoring_type != OBS_MONITORING_TYPE_NONE;
	now_on = type != OBS_MONITORING_TYPE_NONE;

	if (was_on != now_on) {
		if (!was_on) {
			source->monitor = audio_monitor_create(source);
		} else {
			audio_monitor_destroy(source->monitor);
			source->monitor = NULL;
		}
	}

	source->monitoring_type = type;
}