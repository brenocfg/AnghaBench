#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int flags; } ;
struct net_device {int dummy; } ;
struct mwifiex_private {scalar_t__ bss_type; int /*<<< orphan*/  adapter; scalar_t__ media_connected; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MSG ; 
 scalar_t__ MWIFIEX_BSS_TYPE_STA ; 
 int WIPHY_FLAG_SUPPORTS_TDLS ; 
#define  WLAN_PUB_ACTION_TDLS_DISCOVER_RES 133 
#define  WLAN_TDLS_DISCOVERY_REQUEST 132 
#define  WLAN_TDLS_SETUP_CONFIRM 131 
#define  WLAN_TDLS_SETUP_REQUEST 130 
#define  WLAN_TDLS_SETUP_RESPONSE 129 
#define  WLAN_TDLS_TEARDOWN 128 
 int /*<<< orphan*/  mwifiex_add_auto_tdls_peer (struct mwifiex_private*,int const*) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int const*,...) ; 
 struct mwifiex_private* mwifiex_netdev_get_priv (struct net_device*) ; 
 int mwifiex_send_tdls_action_frame (struct mwifiex_private*,int const*,int,int,int /*<<< orphan*/ ,int const*,size_t) ; 
 int mwifiex_send_tdls_data_frame (struct mwifiex_private*,int const*,int,int,int /*<<< orphan*/ ,int const*,size_t) ; 

__attribute__((used)) static int
mwifiex_cfg80211_tdls_mgmt(struct wiphy *wiphy, struct net_device *dev,
			   const u8 *peer, u8 action_code, u8 dialog_token,
			   u16 status_code, u32 peer_capability,
			   bool initiator, const u8 *extra_ies,
			   size_t extra_ies_len)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(dev);
	int ret;

	if (!(wiphy->flags & WIPHY_FLAG_SUPPORTS_TDLS))
		return -ENOTSUPP;

	/* make sure we are in station mode and connected */
	if (!(priv->bss_type == MWIFIEX_BSS_TYPE_STA && priv->media_connected))
		return -ENOTSUPP;

	switch (action_code) {
	case WLAN_TDLS_SETUP_REQUEST:
		mwifiex_dbg(priv->adapter, MSG,
			    "Send TDLS Setup Request to %pM status_code=%d\n",
			    peer, status_code);
		mwifiex_add_auto_tdls_peer(priv, peer);
		ret = mwifiex_send_tdls_data_frame(priv, peer, action_code,
						   dialog_token, status_code,
						   extra_ies, extra_ies_len);
		break;
	case WLAN_TDLS_SETUP_RESPONSE:
		mwifiex_add_auto_tdls_peer(priv, peer);
		mwifiex_dbg(priv->adapter, MSG,
			    "Send TDLS Setup Response to %pM status_code=%d\n",
			    peer, status_code);
		ret = mwifiex_send_tdls_data_frame(priv, peer, action_code,
						   dialog_token, status_code,
						   extra_ies, extra_ies_len);
		break;
	case WLAN_TDLS_SETUP_CONFIRM:
		mwifiex_dbg(priv->adapter, MSG,
			    "Send TDLS Confirm to %pM status_code=%d\n", peer,
			    status_code);
		ret = mwifiex_send_tdls_data_frame(priv, peer, action_code,
						   dialog_token, status_code,
						   extra_ies, extra_ies_len);
		break;
	case WLAN_TDLS_TEARDOWN:
		mwifiex_dbg(priv->adapter, MSG,
			    "Send TDLS Tear down to %pM\n", peer);
		ret = mwifiex_send_tdls_data_frame(priv, peer, action_code,
						   dialog_token, status_code,
						   extra_ies, extra_ies_len);
		break;
	case WLAN_TDLS_DISCOVERY_REQUEST:
		mwifiex_dbg(priv->adapter, MSG,
			    "Send TDLS Discovery Request to %pM\n", peer);
		ret = mwifiex_send_tdls_data_frame(priv, peer, action_code,
						   dialog_token, status_code,
						   extra_ies, extra_ies_len);
		break;
	case WLAN_PUB_ACTION_TDLS_DISCOVER_RES:
		mwifiex_dbg(priv->adapter, MSG,
			    "Send TDLS Discovery Response to %pM\n", peer);
		ret = mwifiex_send_tdls_action_frame(priv, peer, action_code,
						   dialog_token, status_code,
						   extra_ies, extra_ies_len);
		break;
	default:
		mwifiex_dbg(priv->adapter, ERROR,
			    "Unknown TDLS mgmt/action frame %pM\n", peer);
		ret = -EINVAL;
		break;
	}

	return ret;
}