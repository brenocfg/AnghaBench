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
struct devlink_param {scalar_t__ generic; int /*<<< orphan*/  supported_cmodes; int /*<<< orphan*/  name; } ;
struct devlink {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int devlink_param_driver_verify (struct devlink_param const*) ; 
 int devlink_param_generic_verify (struct devlink_param const*) ; 
 int devlink_param_register_one (struct devlink*,struct devlink_param const*) ; 
 int /*<<< orphan*/  devlink_param_unregister_one (struct devlink*,struct devlink_param const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int devlink_params_register(struct devlink *devlink,
			    const struct devlink_param *params,
			    size_t params_count)
{
	const struct devlink_param *param = params;
	int i;
	int err;

	mutex_lock(&devlink->lock);
	for (i = 0; i < params_count; i++, param++) {
		if (!param || !param->name || !param->supported_cmodes) {
			err = -EINVAL;
			goto rollback;
		}
		if (param->generic) {
			err = devlink_param_generic_verify(param);
			if (err)
				goto rollback;
		} else {
			err = devlink_param_driver_verify(param);
			if (err)
				goto rollback;
		}
		err = devlink_param_register_one(devlink, param);
		if (err)
			goto rollback;
	}

	mutex_unlock(&devlink->lock);
	return 0;

rollback:
	if (!i)
		goto unlock;
	for (param--; i > 0; i--, param--)
		devlink_param_unregister_one(devlink, param);
unlock:
	mutex_unlock(&devlink->lock);
	return err;
}