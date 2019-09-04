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
struct devlink_port {int type; void* type_dev; } ;
typedef  enum devlink_port_type { ____Placeholder_devlink_port_type } devlink_port_type ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_PORT_NEW ; 
 int /*<<< orphan*/  devlink_port_notify (struct devlink_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __devlink_port_type_set(struct devlink_port *devlink_port,
				    enum devlink_port_type type,
				    void *type_dev)
{
	devlink_port->type = type;
	devlink_port->type_dev = type_dev;
	devlink_port_notify(devlink_port, DEVLINK_CMD_PORT_NEW);
}