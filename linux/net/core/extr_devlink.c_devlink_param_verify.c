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

/* Variables and functions */
 int EINVAL ; 
 int devlink_param_driver_verify (struct devlink_param const*) ; 
 int devlink_param_generic_verify (struct devlink_param const*) ; 

__attribute__((used)) static int devlink_param_verify(const struct devlink_param *param)
{
	if (!param || !param->name || !param->supported_cmodes)
		return -EINVAL;
	if (param->generic)
		return devlink_param_generic_verify(param);
	else
		return devlink_param_driver_verify(param);
}