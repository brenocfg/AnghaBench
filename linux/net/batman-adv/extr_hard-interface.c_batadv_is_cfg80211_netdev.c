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
struct net_device {scalar_t__ ieee80211_ptr; } ;

/* Variables and functions */

__attribute__((used)) static bool batadv_is_cfg80211_netdev(struct net_device *net_device)
{
	if (!net_device)
		return false;

	/* cfg80211 drivers have to set ieee80211_ptr */
	if (net_device->ieee80211_ptr)
		return true;

	return false;
}