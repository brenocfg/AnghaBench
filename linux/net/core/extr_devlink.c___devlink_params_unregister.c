#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct list_head {int dummy; } ;
struct devlink_param {int dummy; } ;
struct devlink {int /*<<< orphan*/  lock; } ;
typedef  enum devlink_command { ____Placeholder_devlink_command } devlink_command ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_param_unregister_one (struct devlink*,int /*<<< orphan*/ ,struct list_head*,struct devlink_param const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __devlink_params_unregister(struct devlink *devlink,
					unsigned int port_index,
					struct list_head *param_list,
					const struct devlink_param *params,
					size_t params_count,
					enum devlink_command cmd)
{
	const struct devlink_param *param = params;
	int i;

	mutex_lock(&devlink->lock);
	for (i = 0; i < params_count; i++, param++)
		devlink_param_unregister_one(devlink, 0, param_list, param,
					     cmd);
	mutex_unlock(&devlink->lock);
}