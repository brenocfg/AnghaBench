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
struct devlink_health_reporter {int health_state; scalar_t__ last_recovery_ts; scalar_t__ auto_recover; int /*<<< orphan*/  dump_lock; TYPE_1__* ops; int /*<<< orphan*/  graceful_period; int /*<<< orphan*/  error_count; struct devlink* devlink; } ;
struct devlink {int dummy; } ;
typedef  enum devlink_health_reporter_state { ____Placeholder_devlink_health_reporter_state } devlink_health_reporter_state ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 void* DEVLINK_HEALTH_REPORTER_STATE_ERROR ; 
 int DEVLINK_HEALTH_REPORTER_STATE_HEALTHY ; 
 int ECANCELED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  devlink_health_do_dump (struct devlink_health_reporter*,void*) ; 
 int devlink_health_reporter_recover (struct devlink_health_reporter*,void*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_devlink_health_recover_aborted (struct devlink*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  trace_devlink_health_report (struct devlink*,int /*<<< orphan*/ ,char const*) ; 

int devlink_health_report(struct devlink_health_reporter *reporter,
			  const char *msg, void *priv_ctx)
{
	enum devlink_health_reporter_state prev_health_state;
	struct devlink *devlink = reporter->devlink;

	/* write a log message of the current error */
	WARN_ON(!msg);
	trace_devlink_health_report(devlink, reporter->ops->name, msg);
	reporter->error_count++;
	prev_health_state = reporter->health_state;
	reporter->health_state = DEVLINK_HEALTH_REPORTER_STATE_ERROR;

	/* abort if the previous error wasn't recovered */
	if (reporter->auto_recover &&
	    (prev_health_state != DEVLINK_HEALTH_REPORTER_STATE_HEALTHY ||
	     jiffies - reporter->last_recovery_ts <
	     msecs_to_jiffies(reporter->graceful_period))) {
		trace_devlink_health_recover_aborted(devlink,
						     reporter->ops->name,
						     reporter->health_state,
						     jiffies -
						     reporter->last_recovery_ts);
		return -ECANCELED;
	}

	reporter->health_state = DEVLINK_HEALTH_REPORTER_STATE_ERROR;

	mutex_lock(&reporter->dump_lock);
	/* store current dump of current error, for later analysis */
	devlink_health_do_dump(reporter, priv_ctx);
	mutex_unlock(&reporter->dump_lock);

	if (reporter->auto_recover)
		return devlink_health_reporter_recover(reporter, priv_ctx);

	return 0;
}