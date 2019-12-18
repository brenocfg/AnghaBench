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
typedef  void* u32 ;
struct TYPE_2__ {void* split_subport_number; void* port_number; } ;
struct devlink_port_attrs {int split; TYPE_1__ phys; } ;
struct devlink_port {struct devlink_port_attrs attrs; } ;
typedef  enum devlink_port_flavour { ____Placeholder_devlink_port_flavour } devlink_port_flavour ;

/* Variables and functions */
 int __devlink_port_attrs_set (struct devlink_port*,int,unsigned char const*,unsigned char) ; 

void devlink_port_attrs_set(struct devlink_port *devlink_port,
			    enum devlink_port_flavour flavour,
			    u32 port_number, bool split,
			    u32 split_subport_number,
			    const unsigned char *switch_id,
			    unsigned char switch_id_len)
{
	struct devlink_port_attrs *attrs = &devlink_port->attrs;
	int ret;

	ret = __devlink_port_attrs_set(devlink_port, flavour,
				       switch_id, switch_id_len);
	if (ret)
		return;
	attrs->split = split;
	attrs->phys.port_number = port_number;
	attrs->phys.split_subport_number = split_subport_number;
}