#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {TYPE_2__* current_bss; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  vht_capa_mod_mask; int /*<<< orphan*/  ht_capa_mod_mask; } ;
struct cfg80211_registered_device {TYPE_3__ wiphy; } ;
struct cfg80211_assoc_request {int /*<<< orphan*/  bss; int /*<<< orphan*/  vht_capa_mask; int /*<<< orphan*/  ht_capa_mask; int /*<<< orphan*/  prev_bssid; } ;
struct TYPE_5__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_6__ {TYPE_1__ pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int EALREADY ; 
 int ENOENT ; 
 int /*<<< orphan*/  IEEE80211_BSS_TYPE_ESS ; 
 int /*<<< orphan*/  IEEE80211_PRIVACY_ANY ; 
 int /*<<< orphan*/  bss_from_pub (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_get_bss (TYPE_3__*,struct ieee80211_channel*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_hold_bss (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_oper_and_ht_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_oper_and_vht_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_put_bss (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdev_assoc (struct cfg80211_registered_device*,struct net_device*,struct cfg80211_assoc_request*) ; 

int cfg80211_mlme_assoc(struct cfg80211_registered_device *rdev,
			struct net_device *dev,
			struct ieee80211_channel *chan,
			const u8 *bssid,
			const u8 *ssid, int ssid_len,
			struct cfg80211_assoc_request *req)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	int err;

	ASSERT_WDEV_LOCK(wdev);

	if (wdev->current_bss &&
	    (!req->prev_bssid || !ether_addr_equal(wdev->current_bss->pub.bssid,
						   req->prev_bssid)))
		return -EALREADY;

	cfg80211_oper_and_ht_capa(&req->ht_capa_mask,
				  rdev->wiphy.ht_capa_mod_mask);
	cfg80211_oper_and_vht_capa(&req->vht_capa_mask,
				   rdev->wiphy.vht_capa_mod_mask);

	req->bss = cfg80211_get_bss(&rdev->wiphy, chan, bssid, ssid, ssid_len,
				    IEEE80211_BSS_TYPE_ESS,
				    IEEE80211_PRIVACY_ANY);
	if (!req->bss)
		return -ENOENT;

	err = rdev_assoc(rdev, dev, req);
	if (!err)
		cfg80211_hold_bss(bss_from_pub(req->bss));
	else
		cfg80211_put_bss(&rdev->wiphy, req->bss);

	return err;
}