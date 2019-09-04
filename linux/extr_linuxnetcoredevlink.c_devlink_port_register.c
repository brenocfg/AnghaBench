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
struct devlink_port {unsigned int index; int registered; int /*<<< orphan*/  list; struct devlink* devlink; } ;
struct devlink {int /*<<< orphan*/  lock; int /*<<< orphan*/  port_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_PORT_NEW ; 
 int EEXIST ; 
 scalar_t__ devlink_port_index_exists (struct devlink*,unsigned int) ; 
 int /*<<< orphan*/  devlink_port_notify (struct devlink_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int devlink_port_register(struct devlink *devlink,
			  struct devlink_port *devlink_port,
			  unsigned int port_index)
{
	mutex_lock(&devlink->lock);
	if (devlink_port_index_exists(devlink, port_index)) {
		mutex_unlock(&devlink->lock);
		return -EEXIST;
	}
	devlink_port->devlink = devlink;
	devlink_port->index = port_index;
	devlink_port->registered = true;
	list_add_tail(&devlink_port->list, &devlink->port_list);
	mutex_unlock(&devlink->lock);
	devlink_port_notify(devlink_port, DEVLINK_CMD_PORT_NEW);
	return 0;
}