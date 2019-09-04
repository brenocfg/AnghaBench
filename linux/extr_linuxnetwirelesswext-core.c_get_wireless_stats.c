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
struct iw_statistics {int dummy; } ;

/* Variables and functions */

struct iw_statistics *get_wireless_stats(struct net_device *dev)
{
#ifdef CONFIG_WIRELESS_EXT
	if ((dev->wireless_handlers != NULL) &&
	   (dev->wireless_handlers->get_wireless_stats != NULL))
		return dev->wireless_handlers->get_wireless_stats(dev);
#endif

#ifdef CONFIG_CFG80211_WEXT
	if (dev->ieee80211_ptr &&
	    dev->ieee80211_ptr->wiphy &&
	    dev->ieee80211_ptr->wiphy->wext &&
	    dev->ieee80211_ptr->wiphy->wext->get_wireless_stats)
		return dev->ieee80211_ptr->wiphy->wext->get_wireless_stats(dev);
#endif

	/* not found */
	return NULL;
}