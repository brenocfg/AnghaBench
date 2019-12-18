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
struct TYPE_2__ {int mc_disabled; } ;
struct switchdev_attr {TYPE_1__ u; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; struct net_device* orig_dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCHDEV_ATTR_ID_BRIDGE_MC_DISABLED ; 
 int /*<<< orphan*/  SWITCHDEV_F_DEFER ; 
 int /*<<< orphan*/  switchdev_port_attr_set (struct net_device*,struct switchdev_attr*) ; 

__attribute__((used)) static void br_mc_disabled_update(struct net_device *dev, bool value)
{
	struct switchdev_attr attr = {
		.orig_dev = dev,
		.id = SWITCHDEV_ATTR_ID_BRIDGE_MC_DISABLED,
		.flags = SWITCHDEV_F_DEFER,
		.u.mc_disabled = !value,
	};

	switchdev_port_attr_set(dev, &attr);
}