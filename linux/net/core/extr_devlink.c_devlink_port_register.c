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
struct devlink_port {unsigned int index; int registered; int /*<<< orphan*/  type_warn_dw; int /*<<< orphan*/  param_list; int /*<<< orphan*/  list; int /*<<< orphan*/  type_lock; struct devlink* devlink; } ;
struct devlink {int /*<<< orphan*/  lock; int /*<<< orphan*/  port_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_PORT_NEW ; 
 int EEXIST ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ devlink_port_index_exists (struct devlink*,unsigned int) ; 
 int /*<<< orphan*/  devlink_port_notify (struct devlink_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_port_type_warn ; 
 int /*<<< orphan*/  devlink_port_type_warn_schedule (struct devlink_port*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

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
	spin_lock_init(&devlink_port->type_lock);
	list_add_tail(&devlink_port->list, &devlink->port_list);
	INIT_LIST_HEAD(&devlink_port->param_list);
	mutex_unlock(&devlink->lock);
	INIT_DELAYED_WORK(&devlink_port->type_warn_dw, &devlink_port_type_warn);
	devlink_port_type_warn_schedule(devlink_port);
	devlink_port_notify(devlink_port, DEVLINK_CMD_PORT_NEW);
	return 0;
}