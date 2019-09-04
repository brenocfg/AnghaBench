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
struct wlandevice {int /*<<< orphan*/  (* set_multicast_list ) (struct wlandevice*,struct net_device*) ;} ;
struct net_device {struct wlandevice* ml_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct wlandevice*,struct net_device*) ; 

__attribute__((used)) static void p80211knetdev_set_multicast_list(struct net_device *dev)
{
	struct wlandevice *wlandev = dev->ml_priv;

	/* TODO:  real multicast support as well */

	if (wlandev->set_multicast_list)
		wlandev->set_multicast_list(wlandev, dev);
}