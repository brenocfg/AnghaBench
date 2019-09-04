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
struct nlattr {int dummy; } ;
struct devlink_port {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 size_t DEVLINK_ATTR_PORT_INDEX ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct devlink_port* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct devlink_port* devlink_port_get_by_index (struct devlink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static struct devlink_port *devlink_port_get_from_attrs(struct devlink *devlink,
							struct nlattr **attrs)
{
	if (attrs[DEVLINK_ATTR_PORT_INDEX]) {
		u32 port_index = nla_get_u32(attrs[DEVLINK_ATTR_PORT_INDEX]);
		struct devlink_port *devlink_port;

		devlink_port = devlink_port_get_by_index(devlink, port_index);
		if (!devlink_port)
			return ERR_PTR(-ENODEV);
		return devlink_port;
	}
	return ERR_PTR(-EINVAL);
}