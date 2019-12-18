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
struct devlink_health_reporter {int /*<<< orphan*/  last_recovery_ts; int /*<<< orphan*/  health_state; int /*<<< orphan*/  recovery_count; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* recover ) (struct devlink_health_reporter*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_HEALTH_REPORTER_STATE_HEALTHY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  jiffies ; 
 int stub1 (struct devlink_health_reporter*,void*) ; 

__attribute__((used)) static int
devlink_health_reporter_recover(struct devlink_health_reporter *reporter,
				void *priv_ctx)
{
	int err;

	if (!reporter->ops->recover)
		return -EOPNOTSUPP;

	err = reporter->ops->recover(reporter, priv_ctx);
	if (err)
		return err;

	reporter->recovery_count++;
	reporter->health_state = DEVLINK_HEALTH_REPORTER_STATE_HEALTHY;
	reporter->last_recovery_ts = jiffies;

	return 0;
}