#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {TYPE_3__* ieee80211_ptr; TYPE_4__* wireless_handlers; } ;
struct iw_statistics {int dummy; } ;
struct TYPE_8__ {struct iw_statistics* (* get_wireless_stats ) (struct net_device*) ;} ;
struct TYPE_7__ {TYPE_2__* wiphy; } ;
struct TYPE_6__ {TYPE_1__* wext; } ;
struct TYPE_5__ {struct iw_statistics* (* get_wireless_stats ) (struct net_device*) ;} ;

/* Variables and functions */
 struct iw_statistics* stub1 (struct net_device*) ; 
 struct iw_statistics* stub2 (struct net_device*) ; 

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