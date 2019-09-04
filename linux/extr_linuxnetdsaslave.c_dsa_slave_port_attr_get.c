#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int id_len; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int /*<<< orphan*/  brport_flags_support; TYPE_2__ ppid; } ;
struct switchdev_attr {int id; TYPE_1__ u; } ;
struct net_device {int dummy; } ;
struct dsa_switch_tree {int /*<<< orphan*/  index; } ;
struct dsa_switch {struct dsa_switch_tree* dst; } ;
struct dsa_port {struct dsa_switch* ds; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS_SUPPORT 129 
#define  SWITCHDEV_ATTR_ID_PORT_PARENT_ID 128 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dsa_slave_port_attr_get(struct net_device *dev,
				   struct switchdev_attr *attr)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct dsa_switch *ds = dp->ds;
	struct dsa_switch_tree *dst = ds->dst;

	switch (attr->id) {
	case SWITCHDEV_ATTR_ID_PORT_PARENT_ID:
		attr->u.ppid.id_len = sizeof(dst->index);
		memcpy(&attr->u.ppid.id, &dst->index, attr->u.ppid.id_len);
		break;
	case SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS_SUPPORT:
		attr->u.brport_flags_support = 0;
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}