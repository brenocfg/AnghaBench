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
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  ifindex; } ;
struct ib_device {int /*<<< orphan*/  name; int /*<<< orphan*/  ifindex; } ;
struct devlink_port {scalar_t__ type; scalar_t__ desired_type; int /*<<< orphan*/  type_lock; struct net_device* type_dev; int /*<<< orphan*/  index; } ;
struct devlink {int dummy; } ;
typedef  enum devlink_command { ____Placeholder_devlink_command } devlink_command ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_DESIRED_TYPE ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_IBDEV_NAME ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_INDEX ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_NETDEV_IFINDEX ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_NETDEV_NAME ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_TYPE ; 
 scalar_t__ DEVLINK_PORT_TYPE_ETH ; 
 scalar_t__ DEVLINK_PORT_TYPE_IB ; 
 scalar_t__ DEVLINK_PORT_TYPE_NOTSET ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  devlink_nl_family ; 
 scalar_t__ devlink_nl_port_attrs_put (struct sk_buff*,struct devlink_port*) ; 
 scalar_t__ devlink_nl_put_handle (struct sk_buff*,struct devlink*) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int devlink_nl_port_fill(struct sk_buff *msg, struct devlink *devlink,
				struct devlink_port *devlink_port,
				enum devlink_command cmd, u32 portid,
				u32 seq, int flags)
{
	void *hdr;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	if (!hdr)
		return -EMSGSIZE;

	if (devlink_nl_put_handle(msg, devlink))
		goto nla_put_failure;
	if (nla_put_u32(msg, DEVLINK_ATTR_PORT_INDEX, devlink_port->index))
		goto nla_put_failure;

	spin_lock_bh(&devlink_port->type_lock);
	if (nla_put_u16(msg, DEVLINK_ATTR_PORT_TYPE, devlink_port->type))
		goto nla_put_failure_type_locked;
	if (devlink_port->desired_type != DEVLINK_PORT_TYPE_NOTSET &&
	    nla_put_u16(msg, DEVLINK_ATTR_PORT_DESIRED_TYPE,
			devlink_port->desired_type))
		goto nla_put_failure_type_locked;
	if (devlink_port->type == DEVLINK_PORT_TYPE_ETH) {
		struct net_device *netdev = devlink_port->type_dev;

		if (netdev &&
		    (nla_put_u32(msg, DEVLINK_ATTR_PORT_NETDEV_IFINDEX,
				 netdev->ifindex) ||
		     nla_put_string(msg, DEVLINK_ATTR_PORT_NETDEV_NAME,
				    netdev->name)))
			goto nla_put_failure_type_locked;
	}
	if (devlink_port->type == DEVLINK_PORT_TYPE_IB) {
		struct ib_device *ibdev = devlink_port->type_dev;

		if (ibdev &&
		    nla_put_string(msg, DEVLINK_ATTR_PORT_IBDEV_NAME,
				   ibdev->name))
			goto nla_put_failure_type_locked;
	}
	spin_unlock_bh(&devlink_port->type_lock);
	if (devlink_nl_port_attrs_put(msg, devlink_port))
		goto nla_put_failure;

	genlmsg_end(msg, hdr);
	return 0;

nla_put_failure_type_locked:
	spin_unlock_bh(&devlink_port->type_lock);
nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}