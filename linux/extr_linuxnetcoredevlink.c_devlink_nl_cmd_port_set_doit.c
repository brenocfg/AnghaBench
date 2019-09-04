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
struct sk_buff {int dummy; } ;
struct genl_info {scalar_t__* attrs; struct devlink_port** user_ptr; } ;
struct devlink_port {struct devlink* devlink; } ;
struct devlink {int dummy; } ;
typedef  enum devlink_port_type { ____Placeholder_devlink_port_type } devlink_port_type ;

/* Variables and functions */
 size_t DEVLINK_ATTR_PORT_TYPE ; 
 int devlink_port_type_set (struct devlink*,struct devlink_port*,int) ; 
 int nla_get_u16 (scalar_t__) ; 

__attribute__((used)) static int devlink_nl_cmd_port_set_doit(struct sk_buff *skb,
					struct genl_info *info)
{
	struct devlink_port *devlink_port = info->user_ptr[0];
	struct devlink *devlink = devlink_port->devlink;
	int err;

	if (info->attrs[DEVLINK_ATTR_PORT_TYPE]) {
		enum devlink_port_type port_type;

		port_type = nla_get_u16(info->attrs[DEVLINK_ATTR_PORT_TYPE]);
		err = devlink_port_type_set(devlink, devlink_port, port_type);
		if (err)
			return err;
	}
	return 0;
}