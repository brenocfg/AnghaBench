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
struct TYPE_2__ {int mrouter; } ;
struct switchdev_attr {TYPE_1__ u; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; int /*<<< orphan*/  orig_dev; } ;
struct net_bridge_port {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCHDEV_ATTR_ID_PORT_MROUTER ; 
 int /*<<< orphan*/  SWITCHDEV_F_DEFER ; 
 int /*<<< orphan*/  switchdev_port_attr_set (int /*<<< orphan*/ ,struct switchdev_attr*) ; 

__attribute__((used)) static void br_port_mc_router_state_change(struct net_bridge_port *p,
					   bool is_mc_router)
{
	struct switchdev_attr attr = {
		.orig_dev = p->dev,
		.id = SWITCHDEV_ATTR_ID_PORT_MROUTER,
		.flags = SWITCHDEV_F_DEFER,
		.u.mrouter = is_mc_router,
	};

	switchdev_port_attr_set(p->dev, &attr);
}