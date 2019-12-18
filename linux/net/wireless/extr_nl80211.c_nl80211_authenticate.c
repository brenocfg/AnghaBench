#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_9__ {int n_cipher_suites; scalar_t__* cipher_suites; } ;
struct net_device {TYPE_3__* ieee80211_ptr; TYPE_5__ wiphy; TYPE_1__* ops; } ;
struct TYPE_7__ {scalar_t__ key_len; scalar_t__ cipher; int /*<<< orphan*/ * key; } ;
struct key_parse {int idx; int type; TYPE_2__ p; } ;
struct ieee80211_channel {int dummy; } ;
struct genl_info {scalar_t__* attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_3__* ieee80211_ptr; TYPE_5__ wiphy; TYPE_1__* ops; } ;
typedef  enum nl80211_auth_type { ____Placeholder_nl80211_auth_type } nl80211_auth_type ;
struct TYPE_8__ {scalar_t__ iftype; } ;
struct TYPE_6__ {int /*<<< orphan*/  auth; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NL80211_ATTR_AUTH_DATA ; 
 size_t NL80211_ATTR_AUTH_TYPE ; 
 size_t NL80211_ATTR_IE ; 
 size_t NL80211_ATTR_LOCAL_STATE_CHANGE ; 
 size_t NL80211_ATTR_MAC ; 
 size_t NL80211_ATTR_SSID ; 
 size_t NL80211_ATTR_WIPHY_FREQ ; 
 int NL80211_AUTHTYPE_FILS_PK ; 
 int NL80211_AUTHTYPE_FILS_SK ; 
 int NL80211_AUTHTYPE_FILS_SK_PFS ; 
 int NL80211_AUTHTYPE_SAE ; 
 int /*<<< orphan*/  NL80211_CMD_AUTHENTICATE ; 
 scalar_t__ NL80211_IFTYPE_P2P_CLIENT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int NL80211_KEYTYPE_GROUP ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP104 ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP40 ; 
 scalar_t__ WLAN_KEY_LEN_WEP104 ; 
 scalar_t__ WLAN_KEY_LEN_WEP40 ; 
 int cfg80211_mlme_auth (struct net_device*,struct net_device*,struct ieee80211_channel*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/  const*,int) ; 
 struct ieee80211_channel* nl80211_get_valid_chan (TYPE_5__*,scalar_t__) ; 
 int nl80211_parse_key (struct genl_info*,struct key_parse*) ; 
 int /*<<< orphan*/  nl80211_valid_auth_type (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nla_data (scalar_t__) ; 
 int nla_get_u32 (scalar_t__) ; 
 int nla_len (scalar_t__) ; 
 int /*<<< orphan*/  wdev_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  wdev_unlock (TYPE_3__*) ; 

__attribute__((used)) static int nl80211_authenticate(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct ieee80211_channel *chan;
	const u8 *bssid, *ssid, *ie = NULL, *auth_data = NULL;
	int err, ssid_len, ie_len = 0, auth_data_len = 0;
	enum nl80211_auth_type auth_type;
	struct key_parse key;
	bool local_state_change;

	if (!info->attrs[NL80211_ATTR_MAC])
		return -EINVAL;

	if (!info->attrs[NL80211_ATTR_AUTH_TYPE])
		return -EINVAL;

	if (!info->attrs[NL80211_ATTR_SSID])
		return -EINVAL;

	if (!info->attrs[NL80211_ATTR_WIPHY_FREQ])
		return -EINVAL;

	err = nl80211_parse_key(info, &key);
	if (err)
		return err;

	if (key.idx >= 0) {
		if (key.type != -1 && key.type != NL80211_KEYTYPE_GROUP)
			return -EINVAL;
		if (!key.p.key || !key.p.key_len)
			return -EINVAL;
		if ((key.p.cipher != WLAN_CIPHER_SUITE_WEP40 ||
		     key.p.key_len != WLAN_KEY_LEN_WEP40) &&
		    (key.p.cipher != WLAN_CIPHER_SUITE_WEP104 ||
		     key.p.key_len != WLAN_KEY_LEN_WEP104))
			return -EINVAL;
		if (key.idx > 3)
			return -EINVAL;
	} else {
		key.p.key_len = 0;
		key.p.key = NULL;
	}

	if (key.idx >= 0) {
		int i;
		bool ok = false;

		for (i = 0; i < rdev->wiphy.n_cipher_suites; i++) {
			if (key.p.cipher == rdev->wiphy.cipher_suites[i]) {
				ok = true;
				break;
			}
		}
		if (!ok)
			return -EINVAL;
	}

	if (!rdev->ops->auth)
		return -EOPNOTSUPP;

	if (dev->ieee80211_ptr->iftype != NL80211_IFTYPE_STATION &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_P2P_CLIENT)
		return -EOPNOTSUPP;

	bssid = nla_data(info->attrs[NL80211_ATTR_MAC]);
	chan = nl80211_get_valid_chan(&rdev->wiphy,
				      info->attrs[NL80211_ATTR_WIPHY_FREQ]);
	if (!chan)
		return -EINVAL;

	ssid = nla_data(info->attrs[NL80211_ATTR_SSID]);
	ssid_len = nla_len(info->attrs[NL80211_ATTR_SSID]);

	if (info->attrs[NL80211_ATTR_IE]) {
		ie = nla_data(info->attrs[NL80211_ATTR_IE]);
		ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
	}

	auth_type = nla_get_u32(info->attrs[NL80211_ATTR_AUTH_TYPE]);
	if (!nl80211_valid_auth_type(rdev, auth_type, NL80211_CMD_AUTHENTICATE))
		return -EINVAL;

	if ((auth_type == NL80211_AUTHTYPE_SAE ||
	     auth_type == NL80211_AUTHTYPE_FILS_SK ||
	     auth_type == NL80211_AUTHTYPE_FILS_SK_PFS ||
	     auth_type == NL80211_AUTHTYPE_FILS_PK) &&
	    !info->attrs[NL80211_ATTR_AUTH_DATA])
		return -EINVAL;

	if (info->attrs[NL80211_ATTR_AUTH_DATA]) {
		if (auth_type != NL80211_AUTHTYPE_SAE &&
		    auth_type != NL80211_AUTHTYPE_FILS_SK &&
		    auth_type != NL80211_AUTHTYPE_FILS_SK_PFS &&
		    auth_type != NL80211_AUTHTYPE_FILS_PK)
			return -EINVAL;
		auth_data = nla_data(info->attrs[NL80211_ATTR_AUTH_DATA]);
		auth_data_len = nla_len(info->attrs[NL80211_ATTR_AUTH_DATA]);
		/* need to include at least Auth Transaction and Status Code */
		if (auth_data_len < 4)
			return -EINVAL;
	}

	local_state_change = !!info->attrs[NL80211_ATTR_LOCAL_STATE_CHANGE];

	/*
	 * Since we no longer track auth state, ignore
	 * requests to only change local state.
	 */
	if (local_state_change)
		return 0;

	wdev_lock(dev->ieee80211_ptr);
	err = cfg80211_mlme_auth(rdev, dev, chan, auth_type, bssid,
				 ssid, ssid_len, ie, ie_len,
				 key.p.key, key.p.key_len, key.idx,
				 auth_data, auth_data_len);
	wdev_unlock(dev->ieee80211_ptr);
	return err;
}