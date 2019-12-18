#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct devlink_health_reporter {int health_state; TYPE_1__* ops; int /*<<< orphan*/  devlink; } ;
typedef  enum devlink_health_reporter_state { ____Placeholder_devlink_health_reporter_state } devlink_health_reporter_state ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int DEVLINK_HEALTH_REPORTER_STATE_ERROR ; 
 int DEVLINK_HEALTH_REPORTER_STATE_HEALTHY ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  trace_devlink_health_reporter_state_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
devlink_health_reporter_state_update(struct devlink_health_reporter *reporter,
				     enum devlink_health_reporter_state state)
{
	if (WARN_ON(state != DEVLINK_HEALTH_REPORTER_STATE_HEALTHY &&
		    state != DEVLINK_HEALTH_REPORTER_STATE_ERROR))
		return;

	if (reporter->health_state == state)
		return;

	reporter->health_state = state;
	trace_devlink_health_reporter_state_update(reporter->devlink,
						   reporter->ops->name, state);
}