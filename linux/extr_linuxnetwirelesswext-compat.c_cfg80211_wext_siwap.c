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
struct wireless_dev {int iftype; } ;
struct sockaddr {int dummy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  NL80211_IFTYPE_ADHOC 130 
#define  NL80211_IFTYPE_STATION 129 
#define  NL80211_IFTYPE_WDS 128 
 int cfg80211_ibss_wext_siwap (struct net_device*,struct iw_request_info*,struct sockaddr*,char*) ; 
 int cfg80211_mgd_wext_siwap (struct net_device*,struct iw_request_info*,struct sockaddr*,char*) ; 
 int cfg80211_wds_wext_siwap (struct net_device*,struct iw_request_info*,struct sockaddr*,char*) ; 

__attribute__((used)) static int cfg80211_wext_siwap(struct net_device *dev,
			       struct iw_request_info *info,
			       struct sockaddr *ap_addr, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;

	switch (wdev->iftype) {
	case NL80211_IFTYPE_ADHOC:
		return cfg80211_ibss_wext_siwap(dev, info, ap_addr, extra);
	case NL80211_IFTYPE_STATION:
		return cfg80211_mgd_wext_siwap(dev, info, ap_addr, extra);
	case NL80211_IFTYPE_WDS:
		return cfg80211_wds_wext_siwap(dev, info, ap_addr, extra);
	default:
		return -EOPNOTSUPP;
	}
}