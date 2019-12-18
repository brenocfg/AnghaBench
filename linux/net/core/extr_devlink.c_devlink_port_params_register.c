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
struct devlink_port {int /*<<< orphan*/  param_list; int /*<<< orphan*/  index; int /*<<< orphan*/  devlink; } ;
struct devlink_param {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_PORT_PARAM_DEL ; 
 int /*<<< orphan*/  DEVLINK_CMD_PORT_PARAM_NEW ; 
 int __devlink_params_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct devlink_param const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int devlink_port_params_register(struct devlink_port *devlink_port,
				 const struct devlink_param *params,
				 size_t params_count)
{
	return __devlink_params_register(devlink_port->devlink,
					 devlink_port->index,
					 &devlink_port->param_list, params,
					 params_count,
					 DEVLINK_CMD_PORT_PARAM_NEW,
					 DEVLINK_CMD_PORT_PARAM_DEL);
}