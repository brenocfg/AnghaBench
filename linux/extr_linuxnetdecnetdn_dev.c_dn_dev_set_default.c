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
struct net_device {int /*<<< orphan*/  dn_ptr; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 struct net_device* decnet_default_device ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  dndev_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dn_dev_set_default(struct net_device *dev, int force)
{
	struct net_device *old = NULL;
	int rv = -EBUSY;
	if (!dev->dn_ptr)
		return -ENODEV;

	spin_lock(&dndev_lock);
	if (force || decnet_default_device == NULL) {
		old = decnet_default_device;
		decnet_default_device = dev;
		rv = 0;
	}
	spin_unlock(&dndev_lock);

	if (old)
		dev_put(old);
	return rv;
}