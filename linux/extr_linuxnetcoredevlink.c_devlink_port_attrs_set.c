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
typedef  void* u32 ;
struct devlink_port_attrs {int set; int flavour; int split; void* split_subport_number; void* port_number; } ;
struct devlink_port {struct devlink_port_attrs attrs; } ;
typedef  enum devlink_port_flavour { ____Placeholder_devlink_port_flavour } devlink_port_flavour ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_PORT_NEW ; 
 int /*<<< orphan*/  devlink_port_notify (struct devlink_port*,int /*<<< orphan*/ ) ; 

void devlink_port_attrs_set(struct devlink_port *devlink_port,
			    enum devlink_port_flavour flavour,
			    u32 port_number, bool split,
			    u32 split_subport_number)
{
	struct devlink_port_attrs *attrs = &devlink_port->attrs;

	attrs->set = true;
	attrs->flavour = flavour;
	attrs->port_number = port_number;
	attrs->split = split;
	attrs->split_subport_number = split_subport_number;
	devlink_port_notify(devlink_port, DEVLINK_CMD_PORT_NEW);
}