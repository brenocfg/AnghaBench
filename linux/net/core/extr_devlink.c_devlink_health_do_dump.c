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
struct devlink_health_reporter {int /*<<< orphan*/  dump_ts; scalar_t__ dump_fmsg; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* dump ) (struct devlink_health_reporter*,scalar_t__,void*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ devlink_fmsg_alloc () ; 
 int devlink_fmsg_obj_nest_end (scalar_t__) ; 
 int devlink_fmsg_obj_nest_start (scalar_t__) ; 
 int /*<<< orphan*/  devlink_health_dump_clear (struct devlink_health_reporter*) ; 
 int /*<<< orphan*/  jiffies ; 
 int stub1 (struct devlink_health_reporter*,scalar_t__,void*) ; 

__attribute__((used)) static int devlink_health_do_dump(struct devlink_health_reporter *reporter,
				  void *priv_ctx)
{
	int err;

	if (!reporter->ops->dump)
		return 0;

	if (reporter->dump_fmsg)
		return 0;

	reporter->dump_fmsg = devlink_fmsg_alloc();
	if (!reporter->dump_fmsg) {
		err = -ENOMEM;
		return err;
	}

	err = devlink_fmsg_obj_nest_start(reporter->dump_fmsg);
	if (err)
		goto dump_err;

	err = reporter->ops->dump(reporter, reporter->dump_fmsg,
				  priv_ctx);
	if (err)
		goto dump_err;

	err = devlink_fmsg_obj_nest_end(reporter->dump_fmsg);
	if (err)
		goto dump_err;

	reporter->dump_ts = jiffies;

	return 0;

dump_err:
	devlink_health_dump_clear(reporter);
	return err;
}