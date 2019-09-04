#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct station_del_parameters {int subtype; scalar_t__ reason_code; int /*<<< orphan*/  mac; } ;
struct sk_buff {int dummy; } ;
struct net_device {TYPE_2__* ops; TYPE_1__* ieee80211_ptr; } ;
struct genl_info {scalar_t__* attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_2__* ops; TYPE_1__* ieee80211_ptr; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_4__ {int /*<<< orphan*/  del_station; } ;
struct TYPE_3__ {scalar_t__ iftype; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IEEE80211_STYPE_DEAUTH ; 
 int IEEE80211_STYPE_DISASSOC ; 
 size_t NL80211_ATTR_MAC ; 
 size_t NL80211_ATTR_MGMT_SUBTYPE ; 
 size_t NL80211_ATTR_REASON_CODE ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_AP_VLAN ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_P2P_GO ; 
 scalar_t__ WLAN_REASON_PREV_AUTH_NOT_VALID ; 
 int /*<<< orphan*/  memset (struct station_del_parameters*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_data (scalar_t__) ; 
 scalar_t__ nla_get_u16 (scalar_t__) ; 
 int nla_get_u8 (scalar_t__) ; 
 int rdev_del_station (struct net_device*,struct net_device*,struct station_del_parameters*) ; 

__attribute__((used)) static int nl80211_del_station(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct station_del_parameters params;

	memset(&params, 0, sizeof(params));

	if (info->attrs[NL80211_ATTR_MAC])
		params.mac = nla_data(info->attrs[NL80211_ATTR_MAC]);

	if (dev->ieee80211_ptr->iftype != NL80211_IFTYPE_AP &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_AP_VLAN &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_MESH_POINT &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_P2P_GO)
		return -EINVAL;

	if (!rdev->ops->del_station)
		return -EOPNOTSUPP;

	if (info->attrs[NL80211_ATTR_MGMT_SUBTYPE]) {
		params.subtype =
			nla_get_u8(info->attrs[NL80211_ATTR_MGMT_SUBTYPE]);
		if (params.subtype != IEEE80211_STYPE_DISASSOC >> 4 &&
		    params.subtype != IEEE80211_STYPE_DEAUTH >> 4)
			return -EINVAL;
	} else {
		/* Default to Deauthentication frame */
		params.subtype = IEEE80211_STYPE_DEAUTH >> 4;
	}

	if (info->attrs[NL80211_ATTR_REASON_CODE]) {
		params.reason_code =
			nla_get_u16(info->attrs[NL80211_ATTR_REASON_CODE]);
		if (params.reason_code == 0)
			return -EINVAL; /* 0 is reserved */
	} else {
		/* Default to reason code 2 */
		params.reason_code = WLAN_REASON_PREV_AUTH_NOT_VALID;
	}

	return rdev_del_station(rdev, dev, &params);
}