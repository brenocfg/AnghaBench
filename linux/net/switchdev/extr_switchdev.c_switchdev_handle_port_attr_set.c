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
struct switchdev_notifier_port_attr_info {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int __switchdev_handle_port_attr_set (struct net_device*,struct switchdev_notifier_port_attr_info*,int (*) (struct net_device const*),int (*) (struct net_device*,struct switchdev_attr const*,struct switchdev_trans*)) ; 

int switchdev_handle_port_attr_set(struct net_device *dev,
			struct switchdev_notifier_port_attr_info *port_attr_info,
			bool (*check_cb)(const struct net_device *dev),
			int (*set_cb)(struct net_device *dev,
				      const struct switchdev_attr *attr,
				      struct switchdev_trans *trans))
{
	int err;

	err = __switchdev_handle_port_attr_set(dev, port_attr_info, check_cb,
					       set_cb);
	if (err == -EOPNOTSUPP)
		err = 0;
	return err;
}