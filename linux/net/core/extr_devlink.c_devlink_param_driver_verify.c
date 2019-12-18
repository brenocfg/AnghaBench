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
struct devlink_param {int id; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int DEVLINK_PARAM_GENERIC_ID_MAX ; 
 int EEXIST ; 
 int EINVAL ; 
 TYPE_1__* devlink_param_generic ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_param_driver_verify(const struct devlink_param *param)
{
	int i;

	if (param->id <= DEVLINK_PARAM_GENERIC_ID_MAX)
		return -EINVAL;
	/* verify no such name in generic params */
	for (i = 0; i <= DEVLINK_PARAM_GENERIC_ID_MAX; i++)
		if (!strcmp(param->name, devlink_param_generic[i].name))
			return -EEXIST;

	return 0;
}