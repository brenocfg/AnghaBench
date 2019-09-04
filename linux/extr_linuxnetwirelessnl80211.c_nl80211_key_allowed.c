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
struct wireless_dev {int iftype; int /*<<< orphan*/  current_bss; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int EINVAL ; 
 int ENOLINK ; 
#define  NL80211_IFTYPE_ADHOC 141 
#define  NL80211_IFTYPE_AP 140 
#define  NL80211_IFTYPE_AP_VLAN 139 
#define  NL80211_IFTYPE_MESH_POINT 138 
#define  NL80211_IFTYPE_MONITOR 137 
#define  NL80211_IFTYPE_NAN 136 
#define  NL80211_IFTYPE_OCB 135 
#define  NL80211_IFTYPE_P2P_CLIENT 134 
#define  NL80211_IFTYPE_P2P_DEVICE 133 
#define  NL80211_IFTYPE_P2P_GO 132 
#define  NL80211_IFTYPE_STATION 131 
#define  NL80211_IFTYPE_UNSPECIFIED 130 
#define  NL80211_IFTYPE_WDS 129 
#define  NUM_NL80211_IFTYPES 128 

__attribute__((used)) static int nl80211_key_allowed(struct wireless_dev *wdev)
{
	ASSERT_WDEV_LOCK(wdev);

	switch (wdev->iftype) {
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_AP_VLAN:
	case NL80211_IFTYPE_P2P_GO:
	case NL80211_IFTYPE_MESH_POINT:
		break;
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_P2P_CLIENT:
		if (!wdev->current_bss)
			return -ENOLINK;
		break;
	case NL80211_IFTYPE_UNSPECIFIED:
	case NL80211_IFTYPE_OCB:
	case NL80211_IFTYPE_MONITOR:
	case NL80211_IFTYPE_NAN:
	case NL80211_IFTYPE_P2P_DEVICE:
	case NL80211_IFTYPE_WDS:
	case NUM_NL80211_IFTYPES:
		return -EINVAL;
	}

	return 0;
}