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
struct devlink_port {int /*<<< orphan*/  list; struct devlink* devlink; } ;
struct devlink {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_PORT_DEL ; 
 int /*<<< orphan*/  devlink_port_notify (struct devlink_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_port_type_warn_cancel (struct devlink_port*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void devlink_port_unregister(struct devlink_port *devlink_port)
{
	struct devlink *devlink = devlink_port->devlink;

	devlink_port_type_warn_cancel(devlink_port);
	devlink_port_notify(devlink_port, DEVLINK_CMD_PORT_DEL);
	mutex_lock(&devlink->lock);
	list_del(&devlink_port->list);
	mutex_unlock(&devlink->lock);
}