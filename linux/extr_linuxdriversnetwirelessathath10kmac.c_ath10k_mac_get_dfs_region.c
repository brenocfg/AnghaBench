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
typedef  enum wmi_dfs_region { ____Placeholder_wmi_dfs_region } wmi_dfs_region ;
typedef  enum nl80211_dfs_regions { ____Placeholder_nl80211_dfs_regions } nl80211_dfs_regions ;

/* Variables and functions */
#define  NL80211_DFS_ETSI 131 
#define  NL80211_DFS_FCC 130 
#define  NL80211_DFS_JP 129 
#define  NL80211_DFS_UNSET 128 
 int WMI_ETSI_DFS_DOMAIN ; 
 int WMI_FCC_DFS_DOMAIN ; 
 int WMI_MKK4_DFS_DOMAIN ; 
 int WMI_UNINIT_DFS_DOMAIN ; 

__attribute__((used)) static enum wmi_dfs_region
ath10k_mac_get_dfs_region(enum nl80211_dfs_regions dfs_region)
{
	switch (dfs_region) {
	case NL80211_DFS_UNSET:
		return WMI_UNINIT_DFS_DOMAIN;
	case NL80211_DFS_FCC:
		return WMI_FCC_DFS_DOMAIN;
	case NL80211_DFS_ETSI:
		return WMI_ETSI_DFS_DOMAIN;
	case NL80211_DFS_JP:
		return WMI_MKK4_DFS_DOMAIN;
	}
	return WMI_UNINIT_DFS_DOMAIN;
}