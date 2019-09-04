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
struct TYPE_2__ {int /*<<< orphan*/  ageing_time; } ;
struct switchdev_attr {int flags; TYPE_1__ u; int /*<<< orphan*/  id; struct net_device* orig_dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  SWITCHDEV_ATTR_ID_BRIDGE_AGEING_TIME ; 
 int SWITCHDEV_F_DEFER ; 
 int SWITCHDEV_F_SKIP_EOPNOTSUPP ; 
 int /*<<< orphan*/  jiffies_to_clock_t (unsigned long) ; 
 int switchdev_port_attr_set (struct net_device*,struct switchdev_attr*) ; 

int __set_ageing_time(struct net_device *dev, unsigned long t)
{
	struct switchdev_attr attr = {
		.orig_dev = dev,
		.id = SWITCHDEV_ATTR_ID_BRIDGE_AGEING_TIME,
		.flags = SWITCHDEV_F_SKIP_EOPNOTSUPP | SWITCHDEV_F_DEFER,
		.u.ageing_time = jiffies_to_clock_t(t),
	};
	int err;

	err = switchdev_port_attr_set(dev, &attr);
	if (err && err != -EOPNOTSUPP)
		return err;

	return 0;
}