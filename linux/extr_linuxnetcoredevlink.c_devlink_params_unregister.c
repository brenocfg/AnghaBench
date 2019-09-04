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
struct devlink_param {int dummy; } ;
struct devlink {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_param_unregister_one (struct devlink*,struct devlink_param const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void devlink_params_unregister(struct devlink *devlink,
			       const struct devlink_param *params,
			       size_t params_count)
{
	const struct devlink_param *param = params;
	int i;

	mutex_lock(&devlink->lock);
	for (i = 0; i < params_count; i++, param++)
		devlink_param_unregister_one(devlink, param);
	mutex_unlock(&devlink->lock);
}