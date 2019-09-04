#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int flags; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  associated; } ;
struct TYPE_6__ {TYPE_2__ mgd; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  local; TYPE_3__ u; TYPE_1__ vif; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int EOPNOTSUPP ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int WIPHY_FLAG_SUPPORTS_TDLS ; 
#define  WLAN_PUB_ACTION_TDLS_DISCOVER_RES 133 
#define  WLAN_TDLS_DISCOVERY_REQUEST 132 
#define  WLAN_TDLS_SETUP_CONFIRM 131 
#define  WLAN_TDLS_SETUP_REQUEST 130 
#define  WLAN_TDLS_SETUP_RESPONSE 129 
#define  WLAN_TDLS_TEARDOWN 128 
 int /*<<< orphan*/  drv_mgd_protect_tdls_discover (int /*<<< orphan*/ ,struct ieee80211_sub_if_data*) ; 
 int ieee80211_tdls_mgmt_setup (struct wiphy*,struct net_device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,size_t) ; 
 int ieee80211_tdls_mgmt_teardown (struct wiphy*,struct net_device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,size_t) ; 
 int ieee80211_tdls_prep_mgmt_packet (struct wiphy*,struct net_device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdls_dbg (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

int ieee80211_tdls_mgmt(struct wiphy *wiphy, struct net_device *dev,
			const u8 *peer, u8 action_code, u8 dialog_token,
			u16 status_code, u32 peer_capability,
			bool initiator, const u8 *extra_ies,
			size_t extra_ies_len)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	int ret;

	if (!(wiphy->flags & WIPHY_FLAG_SUPPORTS_TDLS))
		return -ENOTSUPP;

	/* make sure we are in managed mode, and associated */
	if (sdata->vif.type != NL80211_IFTYPE_STATION ||
	    !sdata->u.mgd.associated)
		return -EINVAL;

	switch (action_code) {
	case WLAN_TDLS_SETUP_REQUEST:
	case WLAN_TDLS_SETUP_RESPONSE:
		ret = ieee80211_tdls_mgmt_setup(wiphy, dev, peer, action_code,
						dialog_token, status_code,
						peer_capability, initiator,
						extra_ies, extra_ies_len);
		break;
	case WLAN_TDLS_TEARDOWN:
		ret = ieee80211_tdls_mgmt_teardown(wiphy, dev, peer,
						   action_code, dialog_token,
						   status_code,
						   peer_capability, initiator,
						   extra_ies, extra_ies_len);
		break;
	case WLAN_TDLS_DISCOVERY_REQUEST:
		/*
		 * Protect the discovery so we can hear the TDLS discovery
		 * response frame. It is transmitted directly and not buffered
		 * by the AP.
		 */
		drv_mgd_protect_tdls_discover(sdata->local, sdata);
		/* fall-through */
	case WLAN_TDLS_SETUP_CONFIRM:
	case WLAN_PUB_ACTION_TDLS_DISCOVER_RES:
		/* no special handling */
		ret = ieee80211_tdls_prep_mgmt_packet(wiphy, dev, peer,
						      action_code,
						      dialog_token,
						      status_code,
						      peer_capability,
						      initiator, extra_ies,
						      extra_ies_len, 0, NULL);
		break;
	default:
		ret = -EOPNOTSUPP;
		break;
	}

	tdls_dbg(sdata, "TDLS mgmt action %d peer %pM status %d\n",
		 action_code, peer, ret);
	return ret;
}