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
struct devlink {int /*<<< orphan*/  param_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_PARAM_DEL ; 
 void __devlink_params_unregister (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct devlink_param const*,size_t,int /*<<< orphan*/ ) ; 

void devlink_params_unregister(struct devlink *devlink,
			       const struct devlink_param *params,
			       size_t params_count)
{
	return __devlink_params_unregister(devlink, 0, &devlink->param_list,
					   params, params_count,
					   DEVLINK_CMD_PARAM_DEL);
}