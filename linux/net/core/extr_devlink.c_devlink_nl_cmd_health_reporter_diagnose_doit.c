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
struct devlink_health_reporter {TYPE_1__* ops; } ;
struct devlink_fmsg {int dummy; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {int (* diagnose ) (struct devlink_health_reporter*,struct devlink_fmsg*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_HEALTH_REPORTER_DIAGNOSE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 struct devlink_fmsg* devlink_fmsg_alloc () ; 
 int /*<<< orphan*/  devlink_fmsg_free (struct devlink_fmsg*) ; 
 int devlink_fmsg_obj_nest_end (struct devlink_fmsg*) ; 
 int devlink_fmsg_obj_nest_start (struct devlink_fmsg*) ; 
 int devlink_fmsg_snd (struct devlink_fmsg*,struct genl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct devlink_health_reporter* devlink_health_reporter_get_from_info (struct devlink*,struct genl_info*) ; 
 int /*<<< orphan*/  devlink_health_reporter_put (struct devlink_health_reporter*) ; 
 int stub1 (struct devlink_health_reporter*,struct devlink_fmsg*) ; 

__attribute__((used)) static int devlink_nl_cmd_health_reporter_diagnose_doit(struct sk_buff *skb,
							struct genl_info *info)
{
	struct devlink *devlink = info->user_ptr[0];
	struct devlink_health_reporter *reporter;
	struct devlink_fmsg *fmsg;
	int err;

	reporter = devlink_health_reporter_get_from_info(devlink, info);
	if (!reporter)
		return -EINVAL;

	if (!reporter->ops->diagnose) {
		devlink_health_reporter_put(reporter);
		return -EOPNOTSUPP;
	}

	fmsg = devlink_fmsg_alloc();
	if (!fmsg) {
		devlink_health_reporter_put(reporter);
		return -ENOMEM;
	}

	err = devlink_fmsg_obj_nest_start(fmsg);
	if (err)
		goto out;

	err = reporter->ops->diagnose(reporter, fmsg);
	if (err)
		goto out;

	err = devlink_fmsg_obj_nest_end(fmsg);
	if (err)
		goto out;

	err = devlink_fmsg_snd(fmsg, info,
			       DEVLINK_CMD_HEALTH_REPORTER_DIAGNOSE, 0);

out:
	devlink_fmsg_free(fmsg);
	devlink_health_reporter_put(reporter);
	return err;
}