#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wrqu ;
struct TYPE_8__ {int /*<<< orphan*/  sa_data; } ;
union iwreq_data {TYPE_1__ ap_addr; } ;
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {scalar_t__ iftype; TYPE_2__* wiphy; TYPE_3__* current_bss; int /*<<< orphan*/  ssid_len; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct ieee80211_channel {int dummy; } ;
struct cfg80211_bss {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  pub; } ;
struct TYPE_9__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE80211_BSS_TYPE_IBSS ; 
 int /*<<< orphan*/  IEEE80211_PRIVACY_ANY ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 scalar_t__ WARN_ON (int) ; 
 int WIPHY_FLAG_HAS_STATIC_WEP ; 
 TYPE_3__* bss_from_pub (struct cfg80211_bss*) ; 
 struct cfg80211_bss* cfg80211_get_bss (TYPE_2__*,struct ieee80211_channel*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_hold_bss (TYPE_3__*) ; 
 int /*<<< orphan*/  cfg80211_put_bss (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_unhold_bss (TYPE_3__*) ; 
 int /*<<< orphan*/  cfg80211_upload_connect_keys (struct wireless_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union iwreq_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nl80211_send_ibss_bssid (int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_to_rdev (TYPE_2__*) ; 
 int /*<<< orphan*/  wireless_send_event (struct net_device*,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

void __cfg80211_ibss_joined(struct net_device *dev, const u8 *bssid,
			    struct ieee80211_channel *channel)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_bss *bss;
#ifdef CONFIG_CFG80211_WEXT
	union iwreq_data wrqu;
#endif

	if (WARN_ON(wdev->iftype != NL80211_IFTYPE_ADHOC))
		return;

	if (!wdev->ssid_len)
		return;

	bss = cfg80211_get_bss(wdev->wiphy, channel, bssid, NULL, 0,
			       IEEE80211_BSS_TYPE_IBSS, IEEE80211_PRIVACY_ANY);

	if (WARN_ON(!bss))
		return;

	if (wdev->current_bss) {
		cfg80211_unhold_bss(wdev->current_bss);
		cfg80211_put_bss(wdev->wiphy, &wdev->current_bss->pub);
	}

	cfg80211_hold_bss(bss_from_pub(bss));
	wdev->current_bss = bss_from_pub(bss);

	if (!(wdev->wiphy->flags & WIPHY_FLAG_HAS_STATIC_WEP))
		cfg80211_upload_connect_keys(wdev);

	nl80211_send_ibss_bssid(wiphy_to_rdev(wdev->wiphy), dev, bssid,
				GFP_KERNEL);
#ifdef CONFIG_CFG80211_WEXT
	memset(&wrqu, 0, sizeof(wrqu));
	memcpy(wrqu.ap_addr.sa_data, bssid, ETH_ALEN);
	wireless_send_event(dev, SIOCGIWAP, &wrqu, NULL);
#endif
}