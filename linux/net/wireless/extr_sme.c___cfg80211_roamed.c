#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wrqu ;
struct TYPE_10__ {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
struct TYPE_9__ {int /*<<< orphan*/  length; } ;
union iwreq_data {TYPE_2__ ap_addr; TYPE_1__ data; } ;
struct TYPE_11__ {int prev_bssid_valid; int /*<<< orphan*/  prev_bssid; } ;
struct wireless_dev {scalar_t__ iftype; int /*<<< orphan*/  wiphy; int /*<<< orphan*/  netdev; TYPE_3__ wext; TYPE_4__* current_bss; } ;
struct cfg80211_roam_info {TYPE_5__* bss; int /*<<< orphan*/ * resp_ie; int /*<<< orphan*/  resp_ie_len; int /*<<< orphan*/ * req_ie; int /*<<< orphan*/  req_ie_len; } ;
struct TYPE_13__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_12__ {TYPE_5__ pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWEVASSOCREQIE ; 
 int /*<<< orphan*/  IWEVASSOCRESPIE ; 
 scalar_t__ NL80211_IFTYPE_P2P_CLIENT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 scalar_t__ WARN_ON (int) ; 
 TYPE_4__* bss_from_pub (TYPE_5__*) ; 
 int /*<<< orphan*/  cfg80211_hold_bss (TYPE_4__*) ; 
 int /*<<< orphan*/  cfg80211_put_bss (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  cfg80211_unhold_bss (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union iwreq_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nl80211_send_roamed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfg80211_roam_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_to_rdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

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