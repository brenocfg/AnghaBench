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

/* Variables and functions */
 int NL80211_WPA_VERSION_1 ; 
 int NL80211_WPA_VERSION_2 ; 

__attribute__((used)) static bool nl80211_valid_wpa_versions(u32 wpa_versions)
{
	return !(wpa_versions & ~(NL80211_WPA_VERSION_1 |
				  NL80211_WPA_VERSION_2));
}