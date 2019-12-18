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
typedef  int u32 ;
struct batadv_hard_iface {int wifi_flags; } ;

/* Variables and functions */
 int BATADV_HARDIF_WIFI_CFG80211_DIRECT ; 
 int BATADV_HARDIF_WIFI_CFG80211_INDIRECT ; 

bool batadv_is_cfg80211_hardif(struct batadv_hard_iface *hard_iface)
{
	u32 allowed_flags = 0;

	allowed_flags |= BATADV_HARDIF_WIFI_CFG80211_DIRECT;
	allowed_flags |= BATADV_HARDIF_WIFI_CFG80211_INDIRECT;

	return !!(hard_iface->wifi_flags & allowed_flags);
}