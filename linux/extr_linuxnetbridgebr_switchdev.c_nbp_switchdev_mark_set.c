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
struct switchdev_attr {int /*<<< orphan*/  id; int /*<<< orphan*/  orig_dev; } ;
struct net_bridge_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  br; int /*<<< orphan*/  offload_fwd_mark; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  SWITCHDEV_ATTR_ID_PORT_PARENT_ID ; 
 int /*<<< orphan*/  br_switchdev_mark_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int switchdev_port_attr_get (int /*<<< orphan*/ ,struct switchdev_attr*) ; 

int nbp_switchdev_mark_set(struct net_bridge_port *p)
{
	struct switchdev_attr attr = {
		.orig_dev = p->dev,
		.id = SWITCHDEV_ATTR_ID_PORT_PARENT_ID,
	};
	int err;

	ASSERT_RTNL();

	err = switchdev_port_attr_get(p->dev, &attr);
	if (err) {
		if (err == -EOPNOTSUPP)
			return 0;
		return err;
	}

	p->offload_fwd_mark = br_switchdev_mark_get(p->br, p->dev);

	return 0;
}