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

int call_commit_handler(struct net_device *dev)
{
#ifdef CONFIG_WIRELESS_EXT
	if ((netif_running(dev)) &&
	   (dev->wireless_handlers->standard[0] != NULL))
		/* Call the commit handler on the driver */
		return dev->wireless_handlers->standard[0](dev, NULL,
							   NULL, NULL);
	else
		return 0;		/* Command completed successfully */
#else
	/* cfg80211 has no commit */
	return 0;
#endif
}