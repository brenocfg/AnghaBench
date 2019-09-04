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
struct net_device {scalar_t__ dn_ptr; } ;

/* Variables and functions */
 struct net_device* decnet_default_device ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dndev_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct net_device *dn_dev_get_default(void)
{
	struct net_device *dev;

	spin_lock(&dndev_lock);
	dev = decnet_default_device;
	if (dev) {
		if (dev->dn_ptr)
			dev_hold(dev);
		else
			dev = NULL;
	}
	spin_unlock(&dndev_lock);

	return dev;
}