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
struct netdev_phys_item_id {int dummy; } ;
struct net_bridge_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  br; int /*<<< orphan*/  offload_fwd_mark; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  br_switchdev_mark_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dev_get_port_parent_id (int /*<<< orphan*/ ,struct netdev_phys_item_id*,int) ; 

int nbp_switchdev_mark_set(struct net_bridge_port *p)
{
	struct netdev_phys_item_id ppid = { };
	int err;

	ASSERT_RTNL();

	err = dev_get_port_parent_id(p->dev, &ppid, true);
	if (err) {
		if (err == -EOPNOTSUPP)
			return 0;
		return err;
	}

	p->offload_fwd_mark = br_switchdev_mark_get(p->br, p->dev);

	return 0;
}