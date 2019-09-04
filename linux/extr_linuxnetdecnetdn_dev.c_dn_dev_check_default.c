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
struct net_device {int dummy; } ;

/* Variables and functions */
 struct net_device* decnet_default_device ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  dndev_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dn_dev_check_default(struct net_device *dev)
{
	spin_lock(&dndev_lock);
	if (dev == decnet_default_device) {
		decnet_default_device = NULL;
	} else {
		dev = NULL;
	}
	spin_unlock(&dndev_lock);

	if (dev)
		dev_put(dev);
}