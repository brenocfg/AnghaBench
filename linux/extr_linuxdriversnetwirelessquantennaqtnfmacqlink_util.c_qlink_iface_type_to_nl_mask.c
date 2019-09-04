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
typedef  int u16 ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP_VLAN ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  NL80211_IFTYPE_WDS ; 
#define  QLINK_IFTYPE_ADHOC 133 
#define  QLINK_IFTYPE_AP 132 
#define  QLINK_IFTYPE_AP_VLAN 131 
#define  QLINK_IFTYPE_MONITOR 130 
#define  QLINK_IFTYPE_STATION 129 
#define  QLINK_IFTYPE_WDS 128 

u16 qlink_iface_type_to_nl_mask(u16 qlink_type)
{
	u16 result = 0;

	switch (qlink_type) {
	case QLINK_IFTYPE_AP:
		result |= BIT(NL80211_IFTYPE_AP);
		break;
	case QLINK_IFTYPE_STATION:
		result |= BIT(NL80211_IFTYPE_STATION);
		break;
	case QLINK_IFTYPE_ADHOC:
		result |= BIT(NL80211_IFTYPE_ADHOC);
		break;
	case QLINK_IFTYPE_MONITOR:
		result |= BIT(NL80211_IFTYPE_MONITOR);
		break;
	case QLINK_IFTYPE_WDS:
		result |= BIT(NL80211_IFTYPE_WDS);
		break;
	case QLINK_IFTYPE_AP_VLAN:
		result |= BIT(NL80211_IFTYPE_AP_VLAN);
		break;
	}

	return result;
}