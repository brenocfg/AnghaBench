#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wireless_dev {scalar_t__ iftype; int /*<<< orphan*/  wiphy; int /*<<< orphan*/  netdev; TYPE_1__* current_bss; } ;
struct cfg80211_roam_info {int /*<<< orphan*/ * bss; } ;
struct TYPE_4__ {int /*<<< orphan*/  pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NL80211_IFTYPE_P2P_CLIENT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ WARN_ON (int) ; 
 TYPE_1__* bss_from_pub (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_hold_bss (TYPE_1__*) ; 
 int /*<<< orphan*/  cfg80211_put_bss (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_unhold_bss (TYPE_1__*) ; 
 int /*<<< orphan*/  nl80211_send_roamed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfg80211_roam_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_to_rdev (int /*<<< orphan*/ ) ; 

void __cfg80211_roamed(struct wireless_dev *wdev,
		       struct cfg80211_roam_info *info)
{
#ifdef CONFIG_CFG80211_WEXT
	union iwreq_data wrqu;
#endif
	ASSERT_WDEV_LOCK(wdev);

	if (WARN_ON(wdev->iftype != NL80211_IFTYPE_STATION &&
		    wdev->iftype != NL80211_IFTYPE_P2P_CLIENT))
		goto out;

	if (WARN_ON(!wdev->current_bss))
		goto out;

	cfg80211_unhold_bss(wdev->current_bss);
	cfg80211_put_bss(wdev->wiphy, &wdev->current_bss->pub);
	wdev->current_bss = NULL;

	if (WARN_ON(!info->bss))
		return;

	cfg80211_hold_bss(bss_from_pub(info->bss));
	wdev->current_bss = bss_from_pub(info->bss);

	nl80211_send_roamed(wiphy_to_rdev(wdev->wiphy),
			    wdev->netdev, info, GFP_KERNEL);

#ifdef CONFIG_CFG80211_WEXT
	if (info->req_ie) {
		memset(&wrqu, 0, sizeof(wrqu));
		wrqu.data.length = info->req_ie_len;
		wireless_send_event(wdev->netdev, IWEVASSOCREQIE,
				    &wrqu, info->req_ie);
	}

	if (info->resp_ie) {
		memset(&wrqu, 0, sizeof(wrqu));
		wrqu.data.length = info->resp_ie_len;
		wireless_send_event(wdev->netdev, IWEVASSOCRESPIE,
				    &wrqu, info->resp_ie);
	}

	memset(&wrqu, 0, sizeof(wrqu));
	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	memcpy(wrqu.ap_addr.sa_data, info->bss->bssid, ETH_ALEN);
	memcpy(wdev->wext.prev_bssid, info->bss->bssid, ETH_ALEN);
	wdev->wext.prev_bssid_valid = true;
	wireless_send_event(wdev->netdev, SIOCGIWAP, &wrqu, NULL);
#endif

	return;
out:
	cfg80211_put_bss(wdev->wiphy, info->bss);
}