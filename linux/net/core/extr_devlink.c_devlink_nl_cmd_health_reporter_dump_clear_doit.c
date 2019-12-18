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
struct sk_buff {int dummy; } ;
struct genl_info {struct devlink** user_ptr; } ;
struct devlink_health_reporter {int /*<<< orphan*/  dump_lock; TYPE_1__* ops; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dump; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  devlink_health_dump_clear (struct devlink_health_reporter*) ; 
 struct devlink_health_reporter* devlink_health_reporter_get_from_info (struct devlink*,struct genl_info*) ; 
 int /*<<< orphan*/  devlink_health_reporter_put (struct devlink_health_reporter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
devlink_nl_cmd_health_reporter_dump_clear_doit(struct sk_buff *skb,
					       struct genl_info *info)
{
	struct devlink *devlink = info->user_ptr[0];
	struct devlink_health_reporter *reporter;

	reporter = devlink_health_reporter_get_from_info(devlink, info);
	if (!reporter)
		return -EINVAL;

	if (!reporter->ops->dump) {
		devlink_health_reporter_put(reporter);
		return -EOPNOTSUPP;
	}

	mutex_lock(&reporter->dump_lock);
	devlink_health_dump_clear(reporter);
	mutex_unlock(&reporter->dump_lock);
	devlink_health_reporter_put(reporter);
	return 0;
}