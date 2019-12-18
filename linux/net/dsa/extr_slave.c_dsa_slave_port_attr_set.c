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
struct switchdev_trans {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mrouter; int /*<<< orphan*/  brport_flags; int /*<<< orphan*/  ageing_time; int /*<<< orphan*/  vlan_filtering; int /*<<< orphan*/  stp_state; } ;
struct switchdev_attr {int id; TYPE_1__ u; } ;
struct net_device {int dummy; } ;
struct dsa_port {int /*<<< orphan*/  cpu_dp; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SWITCHDEV_ATTR_ID_BRIDGE_AGEING_TIME 133 
#define  SWITCHDEV_ATTR_ID_BRIDGE_MROUTER 132 
#define  SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING 131 
#define  SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS 130 
#define  SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS 129 
#define  SWITCHDEV_ATTR_ID_PORT_STP_STATE 128 
 int dsa_port_ageing_time (struct dsa_port*,int /*<<< orphan*/ ,struct switchdev_trans*) ; 
 int dsa_port_bridge_flags (struct dsa_port*,int /*<<< orphan*/ ,struct switchdev_trans*) ; 
 int dsa_port_mrouter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct switchdev_trans*) ; 
 int dsa_port_pre_bridge_flags (struct dsa_port*,int /*<<< orphan*/ ,struct switchdev_trans*) ; 
 int dsa_port_set_state (struct dsa_port*,int /*<<< orphan*/ ,struct switchdev_trans*) ; 
 int dsa_port_vlan_filtering (struct dsa_port*,int /*<<< orphan*/ ,struct switchdev_trans*) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 

__attribute__((used)) static int dsa_slave_port_attr_set(struct net_device *dev,
				   const struct switchdev_attr *attr,
				   struct switchdev_trans *trans)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	int ret;

	switch (attr->id) {
	case SWITCHDEV_ATTR_ID_PORT_STP_STATE:
		ret = dsa_port_set_state(dp, attr->u.stp_state, trans);
		break;
	case SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING:
		ret = dsa_port_vlan_filtering(dp, attr->u.vlan_filtering,
					      trans);
		break;
	case SWITCHDEV_ATTR_ID_BRIDGE_AGEING_TIME:
		ret = dsa_port_ageing_time(dp, attr->u.ageing_time, trans);
		break;
	case SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS:
		ret = dsa_port_pre_bridge_flags(dp, attr->u.brport_flags,
						trans);
		break;
	case SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS:
		ret = dsa_port_bridge_flags(dp, attr->u.brport_flags, trans);
		break;
	case SWITCHDEV_ATTR_ID_BRIDGE_MROUTER:
		ret = dsa_port_mrouter(dp->cpu_dp, attr->u.mrouter, trans);
		break;
	default:
		ret = -EOPNOTSUPP;
		break;
	}

	return ret;
}