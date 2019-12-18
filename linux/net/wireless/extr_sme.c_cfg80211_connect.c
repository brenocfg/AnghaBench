#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct wireless_dev {scalar_t__ ssid_len; TYPE_6__* current_bss; struct cfg80211_cached_keys* connect_keys; int /*<<< orphan*/  conn_bss_type; int /*<<< orphan*/  ssid; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct TYPE_8__ {int /*<<< orphan*/  vht_capa_mod_mask; int /*<<< orphan*/  ht_capa_mod_mask; } ;
struct cfg80211_registered_device {TYPE_5__* ops; TYPE_2__ wiphy; } ;
struct TYPE_10__ {scalar_t__ cipher_group; int n_ciphers_pairwise; int wep_tx_key; TYPE_3__* wep_keys; scalar_t__* ciphers_pairwise; } ;
struct cfg80211_connect_params {scalar_t__ ssid_len; int key_idx; scalar_t__ pbss; int /*<<< orphan*/  ssid; TYPE_4__ crypto; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  vht_capa_mask; int /*<<< orphan*/  ht_capa_mask; } ;
struct cfg80211_cached_keys {scalar_t__ def; TYPE_3__* params; } ;
struct TYPE_7__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_12__ {TYPE_1__ pub; } ;
struct TYPE_11__ {int /*<<< orphan*/  connect; } ;
struct TYPE_9__ {scalar_t__ cipher; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int EALREADY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  IEEE80211_BSS_TYPE_ESS ; 
 int /*<<< orphan*/  IEEE80211_BSS_TYPE_PBSS ; 
 scalar_t__ WARN_ON (struct cfg80211_cached_keys*) ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP104 ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP40 ; 
 int /*<<< orphan*/  cfg80211_oper_and_ht_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_oper_and_vht_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cfg80211_sme_connect (struct wireless_dev*,struct cfg80211_connect_params*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int rdev_connect (struct cfg80211_registered_device*,struct net_device*,struct cfg80211_connect_params*) ; 

int cfg80211_connect(struct cfg80211_registered_device *rdev,
		     struct net_device *dev,
		     struct cfg80211_connect_params *connect,
		     struct cfg80211_cached_keys *connkeys,
		     const u8 *prev_bssid)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	int err;

	ASSERT_WDEV_LOCK(wdev);

	/*
	 * If we have an ssid_len, we're trying to connect or are
	 * already connected, so reject a new SSID unless it's the
	 * same (which is the case for re-association.)
	 */
	if (wdev->ssid_len &&
	    (wdev->ssid_len != connect->ssid_len ||
	     memcmp(wdev->ssid, connect->ssid, wdev->ssid_len)))
		return -EALREADY;

	/*
	 * If connected, reject (re-)association unless prev_bssid
	 * matches the current BSSID.
	 */
	if (wdev->current_bss) {
		if (!prev_bssid)
			return -EALREADY;
		if (!ether_addr_equal(prev_bssid, wdev->current_bss->pub.bssid))
			return -ENOTCONN;
	}

	/*
	 * Reject if we're in the process of connecting with WEP,
	 * this case isn't very interesting and trying to handle
	 * it would make the code much more complex.
	 */
	if (wdev->connect_keys)
		return -EINPROGRESS;

	cfg80211_oper_and_ht_capa(&connect->ht_capa_mask,
				  rdev->wiphy.ht_capa_mod_mask);
	cfg80211_oper_and_vht_capa(&connect->vht_capa_mask,
				   rdev->wiphy.vht_capa_mod_mask);

	if (connkeys && connkeys->def >= 0) {
		int idx;
		u32 cipher;

		idx = connkeys->def;
		cipher = connkeys->params[idx].cipher;
		/* If given a WEP key we may need it for shared key auth */
		if (cipher == WLAN_CIPHER_SUITE_WEP40 ||
		    cipher == WLAN_CIPHER_SUITE_WEP104) {
			connect->key_idx = idx;
			connect->key = connkeys->params[idx].key;
			connect->key_len = connkeys->params[idx].key_len;

			/*
			 * If ciphers are not set (e.g. when going through
			 * iwconfig), we have to set them appropriately here.
			 */
			if (connect->crypto.cipher_group == 0)
				connect->crypto.cipher_group = cipher;

			if (connect->crypto.n_ciphers_pairwise == 0) {
				connect->crypto.n_ciphers_pairwise = 1;
				connect->crypto.ciphers_pairwise[0] = cipher;
			}
		}

		connect->crypto.wep_keys = connkeys->params;
		connect->crypto.wep_tx_key = connkeys->def;
	} else {
		if (WARN_ON(connkeys))
			return -EINVAL;
	}

	wdev->connect_keys = connkeys;
	memcpy(wdev->ssid, connect->ssid, connect->ssid_len);
	wdev->ssid_len = connect->ssid_len;

	wdev->conn_bss_type = connect->pbss ? IEEE80211_BSS_TYPE_PBSS :
					      IEEE80211_BSS_TYPE_ESS;

	if (!rdev->ops->connect)
		err = cfg80211_sme_connect(wdev, connect, prev_bssid);
	else
		err = rdev_connect(rdev, dev, connect);

	if (err) {
		wdev->connect_keys = NULL;
		/*
		 * This could be reassoc getting refused, don't clear
		 * ssid_len in that case.
		 */
		if (!wdev->current_bss)
			wdev->ssid_len = 0;
		return err;
	}

	return 0;
}