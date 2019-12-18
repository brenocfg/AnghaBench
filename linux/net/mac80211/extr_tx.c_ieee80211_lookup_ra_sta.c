#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sta_info {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_13__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_10__ {int /*<<< orphan*/  remote_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  sta; } ;
struct TYPE_14__ {TYPE_6__ mgd; TYPE_3__ wds; TYPE_2__ vlan; } ;
struct TYPE_12__ {TYPE_4__* wiphy; int /*<<< orphan*/  use_4addr; } ;
struct TYPE_8__ {int type; } ;
struct ieee80211_sub_if_data {TYPE_7__ u; TYPE_5__ wdev; TYPE_1__ vif; } ;
struct TYPE_11__ {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int ENOLINK ; 
 struct sta_info* ERR_PTR (int /*<<< orphan*/ ) ; 
#define  NL80211_IFTYPE_ADHOC 134 
#define  NL80211_IFTYPE_AP 133 
#define  NL80211_IFTYPE_AP_VLAN 132 
#define  NL80211_IFTYPE_MESH_POINT 131 
#define  NL80211_IFTYPE_OCB 130 
#define  NL80211_IFTYPE_STATION 129 
#define  NL80211_IFTYPE_WDS 128 
 int WIPHY_FLAG_SUPPORTS_TDLS ; 
 int /*<<< orphan*/  WLAN_STA_TDLS_PEER ; 
 int /*<<< orphan*/  WLAN_STA_TDLS_PEER_AUTH ; 
 int /*<<< orphan*/  ieee80211_is_tdls_setup (struct sk_buff*) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 struct sta_info* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 struct sta_info* sta_info_get_bss (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_lookup_ra_sta(struct ieee80211_sub_if_data *sdata,
				   struct sk_buff *skb,
				   struct sta_info **sta_out)
{
	struct sta_info *sta;

	switch (sdata->vif.type) {
	case NL80211_IFTYPE_AP_VLAN:
		sta = rcu_dereference(sdata->u.vlan.sta);
		if (sta) {
			*sta_out = sta;
			return 0;
		} else if (sdata->wdev.use_4addr) {
			return -ENOLINK;
		}
		/* fall through */
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_OCB:
	case NL80211_IFTYPE_ADHOC:
		if (is_multicast_ether_addr(skb->data)) {
			*sta_out = ERR_PTR(-ENOENT);
			return 0;
		}
		sta = sta_info_get_bss(sdata, skb->data);
		break;
	case NL80211_IFTYPE_WDS:
		sta = sta_info_get(sdata, sdata->u.wds.remote_addr);
		break;
#ifdef CONFIG_MAC80211_MESH
	case NL80211_IFTYPE_MESH_POINT:
		/* determined much later */
		*sta_out = NULL;
		return 0;
#endif
	case NL80211_IFTYPE_STATION:
		if (sdata->wdev.wiphy->flags & WIPHY_FLAG_SUPPORTS_TDLS) {
			sta = sta_info_get(sdata, skb->data);
			if (sta && test_sta_flag(sta, WLAN_STA_TDLS_PEER)) {
				if (test_sta_flag(sta,
						  WLAN_STA_TDLS_PEER_AUTH)) {
					*sta_out = sta;
					return 0;
				}

				/*
				 * TDLS link during setup - throw out frames to
				 * peer. Allow TDLS-setup frames to unauthorized
				 * peers for the special case of a link teardown
				 * after a TDLS sta is removed due to being
				 * unreachable.
				 */
				if (!ieee80211_is_tdls_setup(skb))
					return -EINVAL;
			}

		}

		sta = sta_info_get(sdata, sdata->u.mgd.bssid);
		if (!sta)
			return -ENOLINK;
		break;
	default:
		return -EINVAL;
	}

	*sta_out = sta ?: ERR_PTR(-ENOENT);
	return 0;
}