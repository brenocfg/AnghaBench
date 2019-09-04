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
struct ieee80211_network {short capability; } ;

/* Variables and functions */
 short WLAN_CAPABILITY_SHORT_SLOT ; 

short ieee80211_is_shortslot(const struct ieee80211_network *net)
{
	return net->capability & WLAN_CAPABILITY_SHORT_SLOT;
}