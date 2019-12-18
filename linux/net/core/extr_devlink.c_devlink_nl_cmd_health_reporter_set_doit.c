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
struct genl_info {scalar_t__* attrs; struct devlink** user_ptr; } ;
struct devlink_health_reporter {int /*<<< orphan*/  auto_recover; int /*<<< orphan*/  graceful_period; TYPE_1__* ops; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  recover; } ;

/* Variables and functions */
 size_t DEVLINK_ATTR_HEALTH_REPORTER_AUTO_RECOVER ; 
 size_t DEVLINK_ATTR_HEALTH_REPORTER_GRACEFUL_PERIOD ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct devlink_health_reporter* devlink_health_reporter_get_from_info (struct devlink*,struct genl_info*) ; 
 int /*<<< orphan*/  devlink_health_reporter_put (struct devlink_health_reporter*) ; 
 int /*<<< orphan*/  nla_get_u64 (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u8 (scalar_t__) ; 

__attribute__((used)) static int
devlink_nl_cmd_health_reporter_set_doit(struct sk_buff *skb,
					struct genl_info *info)
{
	struct devlink *devlink = info->user_ptr[0];
	struct devlink_health_reporter *reporter;
	int err;

	reporter = devlink_health_reporter_get_from_info(devlink, info);
	if (!reporter)
		return -EINVAL;

	if (!reporter->ops->recover &&
	    (info->attrs[DEVLINK_ATTR_HEALTH_REPORTER_GRACEFUL_PERIOD] ||
	     info->attrs[DEVLINK_ATTR_HEALTH_REPORTER_AUTO_RECOVER])) {
		err = -EOPNOTSUPP;
		goto out;
	}

	if (info->attrs[DEVLINK_ATTR_HEALTH_REPORTER_GRACEFUL_PERIOD])
		reporter->graceful_period =
			nla_get_u64(info->attrs[DEVLINK_ATTR_HEALTH_REPORTER_GRACEFUL_PERIOD]);

	if (info->attrs[DEVLINK_ATTR_HEALTH_REPORTER_AUTO_RECOVER])
		reporter->auto_recover =
			nla_get_u8(info->attrs[DEVLINK_ATTR_HEALTH_REPORTER_AUTO_RECOVER]);

	devlink_health_reporter_put(reporter);
	return 0;
out:
	devlink_health_reporter_put(reporter);
	return err;
}