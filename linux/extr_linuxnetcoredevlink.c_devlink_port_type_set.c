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
struct devlink_port {int type; int desired_type; } ;
struct devlink {TYPE_1__* ops; } ;
typedef  enum devlink_port_type { ____Placeholder_devlink_port_type } devlink_port_type ;
struct TYPE_2__ {int (* port_type_set ) (struct devlink_port*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_PORT_NEW ; 
 int DEVLINK_PORT_TYPE_NOTSET ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  devlink_port_notify (struct devlink_port*,int /*<<< orphan*/ ) ; 
 int stub1 (struct devlink_port*,int) ; 

__attribute__((used)) static int devlink_port_type_set(struct devlink *devlink,
				 struct devlink_port *devlink_port,
				 enum devlink_port_type port_type)

{
	int err;

	if (devlink->ops && devlink->ops->port_type_set) {
		if (port_type == DEVLINK_PORT_TYPE_NOTSET)
			return -EINVAL;
		if (port_type == devlink_port->type)
			return 0;
		err = devlink->ops->port_type_set(devlink_port, port_type);
		if (err)
			return err;
		devlink_port->desired_type = port_type;
		devlink_port_notify(devlink_port, DEVLINK_CMD_PORT_NEW);
		return 0;
	}
	return -EOPNOTSUPP;
}