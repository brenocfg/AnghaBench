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
struct wireless_dev {int dummy; } ;
struct wiphy {int n_vendor_events; struct nl80211_vendor_cmd_info* vendor_events; } ;
struct sk_buff {int dummy; } ;
struct nl80211_vendor_cmd_info {int dummy; } ;
struct cfg80211_registered_device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum nl80211_commands { ____Placeholder_nl80211_commands } nl80211_commands ;
typedef  enum nl80211_attrs { ____Placeholder_nl80211_attrs } nl80211_attrs ;

/* Variables and functions */
#define  NL80211_CMD_TESTMODE 129 
#define  NL80211_CMD_VENDOR 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct sk_buff* __cfg80211_alloc_vendor_skb (struct cfg80211_registered_device*,struct wireless_dev*,int,unsigned int,int /*<<< orphan*/ ,int,int,struct nl80211_vendor_cmd_info const*,int /*<<< orphan*/ ) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (struct wiphy*) ; 

struct sk_buff *__cfg80211_alloc_event_skb(struct wiphy *wiphy,
					   struct wireless_dev *wdev,
					   enum nl80211_commands cmd,
					   enum nl80211_attrs attr,
					   unsigned int portid,
					   int vendor_event_idx,
					   int approxlen, gfp_t gfp)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wiphy);
	const struct nl80211_vendor_cmd_info *info;

	switch (cmd) {
	case NL80211_CMD_TESTMODE:
		if (WARN_ON(vendor_event_idx != -1))
			return NULL;
		info = NULL;
		break;
	case NL80211_CMD_VENDOR:
		if (WARN_ON(vendor_event_idx < 0 ||
			    vendor_event_idx >= wiphy->n_vendor_events))
			return NULL;
		info = &wiphy->vendor_events[vendor_event_idx];
		break;
	default:
		WARN_ON(1);
		return NULL;
	}

	return __cfg80211_alloc_vendor_skb(rdev, wdev, approxlen, portid, 0,
					   cmd, attr, info, gfp);
}