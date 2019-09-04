#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int id_len; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  brport_flags_support; int /*<<< orphan*/  brport_flags; TYPE_2__ ppid; } ;
struct switchdev_attr {int id; TYPE_3__ u; } ;
struct rocker_port {struct rocker* rocker; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct rocker {TYPE_1__ hw; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS 130 
#define  SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS_SUPPORT 129 
#define  SWITCHDEV_ATTR_ID_PORT_PARENT_ID 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct rocker_port* netdev_priv (struct net_device*) ; 
 int rocker_world_port_attr_bridge_flags_get (struct rocker_port const*,int /*<<< orphan*/ *) ; 
 int rocker_world_port_attr_bridge_flags_support_get (struct rocker_port const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rocker_port_attr_get(struct net_device *dev,
				struct switchdev_attr *attr)
{
	const struct rocker_port *rocker_port = netdev_priv(dev);
	const struct rocker *rocker = rocker_port->rocker;
	int err = 0;

	switch (attr->id) {
	case SWITCHDEV_ATTR_ID_PORT_PARENT_ID:
		attr->u.ppid.id_len = sizeof(rocker->hw.id);
		memcpy(&attr->u.ppid.id, &rocker->hw.id, attr->u.ppid.id_len);
		break;
	case SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS:
		err = rocker_world_port_attr_bridge_flags_get(rocker_port,
							      &attr->u.brport_flags);
		break;
	case SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS_SUPPORT:
		err = rocker_world_port_attr_bridge_flags_support_get(rocker_port,
								      &attr->u.brport_flags_support);
		break;
	default:
		return -EOPNOTSUPP;
	}

	return err;
}