#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int features; struct ieee80211_supported_band** bands; } ;
struct sk_buff {int dummy; } ;
struct net_device {TYPE_3__* ieee80211_ptr; struct wiphy wiphy; TYPE_1__* ops; } ;
struct ieee80211_supported_band {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_portid; scalar_t__* attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_3__* ieee80211_ptr; struct wiphy wiphy; TYPE_1__* ops; } ;
struct TYPE_10__ {int width; TYPE_2__* chan; } ;
struct cfg80211_ibss_params {int beacon_interval; int channel_fixed; int privacy; int control_port_over_nl80211; void* userspace_handles_dfs; void* control_port; TYPE_5__ chandef; int /*<<< orphan*/  mcast_rate; int /*<<< orphan*/  ht_capa; int /*<<< orphan*/  ht_capa_mask; int /*<<< orphan*/  basic_rates; void* ie_len; void* ie; void* ssid_len; void* ssid; void* bssid; } ;
struct cfg80211_cached_keys {int dummy; } ;
typedef  int /*<<< orphan*/  ibss ;
struct TYPE_9__ {scalar_t__ iftype; int /*<<< orphan*/  conn_owner_nlportid; } ;
struct TYPE_8__ {size_t band; } ;
struct TYPE_7__ {int /*<<< orphan*/  join_ibss; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct cfg80211_cached_keys*) ; 
 size_t NL80211_ATTR_BEACON_INTERVAL ; 
 size_t NL80211_ATTR_BSS_BASIC_RATES ; 
 size_t NL80211_ATTR_CONTROL_PORT ; 
 size_t NL80211_ATTR_CONTROL_PORT_OVER_NL80211 ; 
 size_t NL80211_ATTR_FREQ_FIXED ; 
 size_t NL80211_ATTR_HANDLE_DFS ; 
 size_t NL80211_ATTR_HT_CAPABILITY ; 
 size_t NL80211_ATTR_HT_CAPABILITY_MASK ; 
 size_t NL80211_ATTR_IE ; 
 size_t NL80211_ATTR_KEYS ; 
 size_t NL80211_ATTR_MAC ; 
 size_t NL80211_ATTR_MCAST_RATE ; 
 size_t NL80211_ATTR_PRIVACY ; 
 size_t NL80211_ATTR_SOCKET_OWNER ; 
 size_t NL80211_ATTR_SSID ; 
#define  NL80211_CHAN_WIDTH_10 135 
#define  NL80211_CHAN_WIDTH_160 134 
#define  NL80211_CHAN_WIDTH_20 133 
#define  NL80211_CHAN_WIDTH_20_NOHT 132 
#define  NL80211_CHAN_WIDTH_40 131 
#define  NL80211_CHAN_WIDTH_5 130 
#define  NL80211_CHAN_WIDTH_80 129 
#define  NL80211_CHAN_WIDTH_80P80 128 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_VHT_IBSS ; 
 int NL80211_FEATURE_HT_IBSS ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int PTR_ERR (struct cfg80211_cached_keys*) ; 
 int __cfg80211_join_ibss (struct net_device*,struct net_device*,struct cfg80211_ibss_params*,struct cfg80211_cached_keys*) ; 
 int /*<<< orphan*/  cfg80211_reg_can_beacon (struct wiphy*,TYPE_5__*,scalar_t__) ; 
 int cfg80211_validate_beacon_int (struct net_device*,scalar_t__,int) ; 
 int ieee80211_get_ratemask (struct ieee80211_supported_band*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_ether_addr (void*) ; 
 int /*<<< orphan*/  kzfree (struct cfg80211_cached_keys*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  memset (struct cfg80211_ibss_params*,int /*<<< orphan*/ ,int) ; 
 int nl80211_parse_chandef (struct net_device*,struct genl_info*,TYPE_5__*) ; 
 struct cfg80211_cached_keys* nl80211_parse_connkeys (struct net_device*,struct genl_info*,int*) ; 
 int /*<<< orphan*/  nl80211_parse_mcast_rate (struct net_device*,int /*<<< orphan*/ ,int) ; 
 void* nla_data (scalar_t__) ; 
 void* nla_get_flag (scalar_t__) ; 
 int nla_get_u32 (scalar_t__) ; 
 void* nla_len (scalar_t__) ; 
 int validate_pae_over_nl80211 (struct net_device*,struct genl_info*) ; 
 int /*<<< orphan*/  wdev_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  wdev_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  wiphy_ext_feature_isset (struct wiphy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_join_ibss(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct cfg80211_ibss_params ibss;
	struct wiphy *wiphy;
	struct cfg80211_cached_keys *connkeys = NULL;
	int err;

	memset(&ibss, 0, sizeof(ibss));

	if (!info->attrs[NL80211_ATTR_SSID] ||
	    !nla_len(info->attrs[NL80211_ATTR_SSID]))
		return -EINVAL;

	ibss.beacon_interval = 100;

	if (info->attrs[NL80211_ATTR_BEACON_INTERVAL])
		ibss.beacon_interval =
			nla_get_u32(info->attrs[NL80211_ATTR_BEACON_INTERVAL]);

	err = cfg80211_validate_beacon_int(rdev, NL80211_IFTYPE_ADHOC,
					   ibss.beacon_interval);
	if (err)
		return err;

	if (!rdev->ops->join_ibss)
		return -EOPNOTSUPP;

	if (dev->ieee80211_ptr->iftype != NL80211_IFTYPE_ADHOC)
		return -EOPNOTSUPP;

	wiphy = &rdev->wiphy;

	if (info->attrs[NL80211_ATTR_MAC]) {
		ibss.bssid = nla_data(info->attrs[NL80211_ATTR_MAC]);

		if (!is_valid_ether_addr(ibss.bssid))
			return -EINVAL;
	}
	ibss.ssid = nla_data(info->attrs[NL80211_ATTR_SSID]);
	ibss.ssid_len = nla_len(info->attrs[NL80211_ATTR_SSID]);

	if (info->attrs[NL80211_ATTR_IE]) {
		ibss.ie = nla_data(info->attrs[NL80211_ATTR_IE]);
		ibss.ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
	}

	err = nl80211_parse_chandef(rdev, info, &ibss.chandef);
	if (err)
		return err;

	if (!cfg80211_reg_can_beacon(&rdev->wiphy, &ibss.chandef,
				     NL80211_IFTYPE_ADHOC))
		return -EINVAL;

	switch (ibss.chandef.width) {
	case NL80211_CHAN_WIDTH_5:
	case NL80211_CHAN_WIDTH_10:
	case NL80211_CHAN_WIDTH_20_NOHT:
		break;
	case NL80211_CHAN_WIDTH_20:
	case NL80211_CHAN_WIDTH_40:
		if (!(rdev->wiphy.features & NL80211_FEATURE_HT_IBSS))
			return -EINVAL;
		break;
	case NL80211_CHAN_WIDTH_80:
	case NL80211_CHAN_WIDTH_80P80:
	case NL80211_CHAN_WIDTH_160:
		if (!(rdev->wiphy.features & NL80211_FEATURE_HT_IBSS))
			return -EINVAL;
		if (!wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_VHT_IBSS))
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	ibss.channel_fixed = !!info->attrs[NL80211_ATTR_FREQ_FIXED];
	ibss.privacy = !!info->attrs[NL80211_ATTR_PRIVACY];

	if (info->attrs[NL80211_ATTR_BSS_BASIC_RATES]) {
		u8 *rates =
			nla_data(info->attrs[NL80211_ATTR_BSS_BASIC_RATES]);
		int n_rates =
			nla_len(info->attrs[NL80211_ATTR_BSS_BASIC_RATES]);
		struct ieee80211_supported_band *sband =
			wiphy->bands[ibss.chandef.chan->band];

		err = ieee80211_get_ratemask(sband, rates, n_rates,
					     &ibss.basic_rates);
		if (err)
			return err;
	}

	if (info->attrs[NL80211_ATTR_HT_CAPABILITY_MASK])
		memcpy(&ibss.ht_capa_mask,
		       nla_data(info->attrs[NL80211_ATTR_HT_CAPABILITY_MASK]),
		       sizeof(ibss.ht_capa_mask));

	if (info->attrs[NL80211_ATTR_HT_CAPABILITY]) {
		if (!info->attrs[NL80211_ATTR_HT_CAPABILITY_MASK])
			return -EINVAL;
		memcpy(&ibss.ht_capa,
		       nla_data(info->attrs[NL80211_ATTR_HT_CAPABILITY]),
		       sizeof(ibss.ht_capa));
	}

	if (info->attrs[NL80211_ATTR_MCAST_RATE] &&
	    !nl80211_parse_mcast_rate(rdev, ibss.mcast_rate,
			nla_get_u32(info->attrs[NL80211_ATTR_MCAST_RATE])))
		return -EINVAL;

	if (ibss.privacy && info->attrs[NL80211_ATTR_KEYS]) {
		bool no_ht = false;

		connkeys = nl80211_parse_connkeys(rdev, info, &no_ht);
		if (IS_ERR(connkeys))
			return PTR_ERR(connkeys);

		if ((ibss.chandef.width != NL80211_CHAN_WIDTH_20_NOHT) &&
		    no_ht) {
			kzfree(connkeys);
			return -EINVAL;
		}
	}

	ibss.control_port =
		nla_get_flag(info->attrs[NL80211_ATTR_CONTROL_PORT]);

	if (info->attrs[NL80211_ATTR_CONTROL_PORT_OVER_NL80211]) {
		int r = validate_pae_over_nl80211(rdev, info);

		if (r < 0) {
			kzfree(connkeys);
			return r;
		}

		ibss.control_port_over_nl80211 = true;
	}

	ibss.userspace_handles_dfs =
		nla_get_flag(info->attrs[NL80211_ATTR_HANDLE_DFS]);

	wdev_lock(dev->ieee80211_ptr);
	err = __cfg80211_join_ibss(rdev, dev, &ibss, connkeys);
	if (err)
		kzfree(connkeys);
	else if (info->attrs[NL80211_ATTR_SOCKET_OWNER])
		dev->ieee80211_ptr->conn_owner_nlportid = info->snd_portid;
	wdev_unlock(dev->ieee80211_ptr);

	return err;
}