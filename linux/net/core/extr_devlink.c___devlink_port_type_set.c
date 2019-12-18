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
struct devlink_port {int type; int /*<<< orphan*/  type_lock; void* type_dev; int /*<<< orphan*/  registered; } ;
typedef  enum devlink_port_type { ____Placeholder_devlink_port_type } devlink_port_type ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_PORT_NEW ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  devlink_port_notify (struct devlink_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_port_type_warn_cancel (struct devlink_port*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __devlink_port_type_set(struct devlink_port *devlink_port,
				    enum devlink_port_type type,
				    void *type_dev)
{
	if (WARN_ON(!devlink_port->registered))
		return;
	devlink_port_type_warn_cancel(devlink_port);
	spin_lock_bh(&devlink_port->type_lock);
	devlink_port->type = type;
	devlink_port->type_dev = type_dev;
	spin_unlock_bh(&devlink_port->type_lock);
	devlink_port_notify(devlink_port, DEVLINK_CMD_PORT_NEW);
}