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
struct devlink_port_attrs {int /*<<< orphan*/  split_subport_number; int /*<<< orphan*/  port_number; int /*<<< orphan*/  split; int /*<<< orphan*/  flavour; int /*<<< orphan*/  set; } ;
struct devlink_port {struct devlink_port_attrs attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_FLAVOUR ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_NUMBER ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_SPLIT_GROUP ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_SPLIT_SUBPORT_NUMBER ; 
 int EMSGSIZE ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_port_attrs_put(struct sk_buff *msg,
				     struct devlink_port *devlink_port)
{
	struct devlink_port_attrs *attrs = &devlink_port->attrs;

	if (!attrs->set)
		return 0;
	if (nla_put_u16(msg, DEVLINK_ATTR_PORT_FLAVOUR, attrs->flavour))
		return -EMSGSIZE;
	if (nla_put_u32(msg, DEVLINK_ATTR_PORT_NUMBER, attrs->port_number))
		return -EMSGSIZE;
	if (!attrs->split)
		return 0;
	if (nla_put_u32(msg, DEVLINK_ATTR_PORT_SPLIT_GROUP, attrs->port_number))
		return -EMSGSIZE;
	if (nla_put_u32(msg, DEVLINK_ATTR_PORT_SPLIT_SUBPORT_NUMBER,
			attrs->split_subport_number))
		return -EMSGSIZE;
	return 0;
}