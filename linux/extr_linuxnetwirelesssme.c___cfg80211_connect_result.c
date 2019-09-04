#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct wireless_dev {scalar_t__ iftype; TYPE_4__* wiphy; TYPE_8__* current_bss; scalar_t__ conn_owner_nlportid; scalar_t__ ssid_len; int /*<<< orphan*/ * connect_keys; int /*<<< orphan*/  conn_bss_type; int /*<<< orphan*/  ssid; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_connect_resp_params {scalar_t__ status; TYPE_7__* bss; int /*<<< orphan*/  bssid; } ;
struct TYPE_20__ {TYPE_2__* channel; } ;
struct TYPE_21__ {TYPE_7__ pub; } ;
struct TYPE_19__ {int flags; } ;
struct TYPE_18__ {TYPE_1__* ops; } ;
struct TYPE_17__ {int /*<<< orphan*/  band; } ;
struct TYPE_16__ {int /*<<< orphan*/  connect; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE80211_PRIVACY_ANY ; 
 scalar_t__ NL80211_IFTYPE_P2P_CLIENT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int WIPHY_FLAG_HAS_STATIC_WEP ; 
 int /*<<< orphan*/  WLAN_EID_COUNTRY ; 
 scalar_t__ WLAN_STATUS_SUCCESS ; 
 TYPE_8__* bss_from_pub (TYPE_7__*) ; 
 TYPE_7__* cfg80211_get_bss (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_hold_bss (TYPE_8__*) ; 
 int /*<<< orphan*/  cfg80211_put_bss (TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  cfg80211_sme_free (struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_unhold_bss (TYPE_8__*) ; 
 int /*<<< orphan*/  cfg80211_upload_connect_keys (struct wireless_dev*) ; 
 scalar_t__* ieee80211_bss_get_ie (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__ const*) ; 
 scalar_t__* kmemdup (scalar_t__ const*,scalar_t__ const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl80211_send_connect_result (TYPE_3__*,struct net_device*,struct cfg80211_connect_resp_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  regulatory_hint_country_ie (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__ const) ; 
 TYPE_3__* wiphy_to_rdev (TYPE_4__*) ; 

void __cfg80211_connect_result(struct net_device *dev,
			       struct cfg80211_connect_resp_params *cr,
			       bool wextev)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	const u8 *country_ie;
#ifdef CONFIG_CFG80211_WEXT
	union iwreq_data wrqu;
#endif

	ASSERT_WDEV_LOCK(wdev);

	if (WARN_ON(wdev->iftype != NL80211_IFTYPE_STATION &&
		    wdev->iftype != NL80211_IFTYPE_P2P_CLIENT)) {
		cfg80211_put_bss(wdev->wiphy, cr->bss);
		return;
	}

	nl80211_send_connect_result(wiphy_to_rdev(wdev->wiphy), dev, cr,
				    GFP_KERNEL);

#ifdef CONFIG_CFG80211_WEXT
	if (wextev) {
		if (cr->req_ie && cr->status == WLAN_STATUS_SUCCESS) {
			memset(&wrqu, 0, sizeof(wrqu));
			wrqu.data.length = cr->req_ie_len;
			wireless_send_event(dev, IWEVASSOCREQIE, &wrqu,
					    cr->req_ie);
		}

		if (cr->resp_ie && cr->status == WLAN_STATUS_SUCCESS) {
			memset(&wrqu, 0, sizeof(wrqu));
			wrqu.data.length = cr->resp_ie_len;
			wireless_send_event(dev, IWEVASSOCRESPIE, &wrqu,
					    cr->resp_ie);
		}

		memset(&wrqu, 0, sizeof(wrqu));
		wrqu.ap_addr.sa_family = ARPHRD_ETHER;
		if (cr->bssid && cr->status == WLAN_STATUS_SUCCESS) {
			memcpy(wrqu.ap_addr.sa_data, cr->bssid, ETH_ALEN);
			memcpy(wdev->wext.prev_bssid, cr->bssid, ETH_ALEN);
			wdev->wext.prev_bssid_valid = true;
		}
		wireless_send_event(dev, SIOCGIWAP, &wrqu, NULL);
	}
#endif

	if (!cr->bss && (cr->status == WLAN_STATUS_SUCCESS)) {
		WARN_ON_ONCE(!wiphy_to_rdev(wdev->wiphy)->ops->connect);
		cr->bss = cfg80211_get_bss(wdev->wiphy, NULL, cr->bssid,
					   wdev->ssid, wdev->ssid_len,
					   wdev->conn_bss_type,
					   IEEE80211_PRIVACY_ANY);
		if (cr->bss)
			cfg80211_hold_bss(bss_from_pub(cr->bss));
	}

	if (wdev->current_bss) {
		cfg80211_unhold_bss(wdev->current_bss);
		cfg80211_put_bss(wdev->wiphy, &wdev->current_bss->pub);
		wdev->current_bss = NULL;
	}

	if (cr->status != WLAN_STATUS_SUCCESS) {
		kzfree(wdev->connect_keys);
		wdev->connect_keys = NULL;
		wdev->ssid_len = 0;
		wdev->conn_owner_nlportid = 0;
		if (cr->bss) {
			cfg80211_unhold_bss(bss_from_pub(cr->bss));
			cfg80211_put_bss(wdev->wiphy, cr->bss);
		}
		cfg80211_sme_free(wdev);
		return;
	}

	if (WARN_ON(!cr->bss))
		return;

	wdev->current_bss = bss_from_pub(cr->bss);

	if (!(wdev->wiphy->flags & WIPHY_FLAG_HAS_STATIC_WEP))
		cfg80211_upload_connect_keys(wdev);

	rcu_read_lock();
	country_ie = ieee80211_bss_get_ie(cr->bss, WLAN_EID_COUNTRY);
	if (!country_ie) {
		rcu_read_unlock();
		return;
	}

	country_ie = kmemdup(country_ie, 2 + country_ie[1], GFP_ATOMIC);
	rcu_read_unlock();

	if (!country_ie)
		return;

	/*
	 * ieee80211_bss_get_ie() ensures we can access:
	 * - country_ie + 2, the start of the country ie data, and
	 * - and country_ie[1] which is the IE length
	 */
	regulatory_hint_country_ie(wdev->wiphy, cr->bss->channel->band,
				   country_ie + 2, country_ie[1]);
	kfree(country_ie);
}