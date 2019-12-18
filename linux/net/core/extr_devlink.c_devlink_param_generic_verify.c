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
struct devlink_param {size_t id; scalar_t__ type; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t DEVLINK_PARAM_GENERIC_ID_MAX ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* devlink_param_generic ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_param_generic_verify(const struct devlink_param *param)
{
	/* verify it match generic parameter by id and name */
	if (param->id > DEVLINK_PARAM_GENERIC_ID_MAX)
		return -EINVAL;
	if (strcmp(param->name, devlink_param_generic[param->id].name))
		return -ENOENT;

	WARN_ON(param->type != devlink_param_generic[param->id].type);

	return 0;
}