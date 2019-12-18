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
typedef  int /*<<< orphan*/  u32 ;
struct devlink_port {int /*<<< orphan*/  index; int /*<<< orphan*/  devlink; int /*<<< orphan*/  param_list; } ;
struct devlink_param_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_PORT_PARAM_NEW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct devlink_param_item* devlink_param_find_by_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_param_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct devlink_param_item*,int /*<<< orphan*/ ) ; 

void devlink_port_param_value_changed(struct devlink_port *devlink_port,
				      u32 param_id)
{
	struct devlink_param_item *param_item;

	param_item = devlink_param_find_by_id(&devlink_port->param_list,
					      param_id);
	WARN_ON(!param_item);

	devlink_param_notify(devlink_port->devlink, devlink_port->index,
			     param_item, DEVLINK_CMD_PORT_PARAM_NEW);
}