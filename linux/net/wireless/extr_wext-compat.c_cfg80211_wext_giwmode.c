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
typedef  int /*<<< orphan*/  u32 ;
struct wireless_dev {int iftype; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IW_MODE_ADHOC ; 
 int /*<<< orphan*/  IW_MODE_AUTO ; 
 int /*<<< orphan*/  IW_MODE_INFRA ; 
 int /*<<< orphan*/  IW_MODE_MASTER ; 
 int /*<<< orphan*/  IW_MODE_MONITOR ; 
 int /*<<< orphan*/  IW_MODE_REPEAT ; 
 int /*<<< orphan*/  IW_MODE_SECOND ; 
#define  NL80211_IFTYPE_ADHOC 133 
#define  NL80211_IFTYPE_AP 132 
#define  NL80211_IFTYPE_AP_VLAN 131 
#define  NL80211_IFTYPE_MONITOR 130 
#define  NL80211_IFTYPE_STATION 129 
#define  NL80211_IFTYPE_WDS 128 

int cfg80211_wext_giwmode(struct net_device *dev, struct iw_request_info *info,
			  u32 *mode, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;

	if (!wdev)
		return -EOPNOTSUPP;

	switch (wdev->iftype) {
	case NL80211_IFTYPE_AP:
		*mode = IW_MODE_MASTER;
		break;
	case NL80211_IFTYPE_STATION:
		*mode = IW_MODE_INFRA;
		break;
	case NL80211_IFTYPE_ADHOC:
		*mode = IW_MODE_ADHOC;
		break;
	case NL80211_IFTYPE_MONITOR:
		*mode = IW_MODE_MONITOR;
		break;
	case NL80211_IFTYPE_WDS:
		*mode = IW_MODE_REPEAT;
		break;
	case NL80211_IFTYPE_AP_VLAN:
		*mode = IW_MODE_SECOND;		/* FIXME */
		break;
	default:
		*mode = IW_MODE_AUTO;
		break;
	}
	return 0;
}