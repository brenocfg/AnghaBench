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
typedef  int /*<<< orphan*/  u8 ;
struct mwifiex_private {int bss_mode; int /*<<< orphan*/  netdev; int /*<<< orphan*/  media_connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  HostCmd_CMD_802_11_AD_HOC_STOP ; 
 int /*<<< orphan*/  HostCmd_CMD_UAP_BSS_STOP ; 
#define  NL80211_IFTYPE_ADHOC 131 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_P2P_CLIENT 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  cfg80211_disconnected (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mwifiex_deauthenticate_infra (struct mwifiex_private*,int /*<<< orphan*/ *) ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int mwifiex_deauthenticate(struct mwifiex_private *priv, u8 *mac)
{
	int ret = 0;

	if (!priv->media_connected)
		return 0;

	switch (priv->bss_mode) {
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_P2P_CLIENT:
		ret = mwifiex_deauthenticate_infra(priv, mac);
		if (ret)
			cfg80211_disconnected(priv->netdev, 0, NULL, 0,
					      true, GFP_KERNEL);
		break;
	case NL80211_IFTYPE_ADHOC:
		return mwifiex_send_cmd(priv, HostCmd_CMD_802_11_AD_HOC_STOP,
					HostCmd_ACT_GEN_SET, 0, NULL, true);
	case NL80211_IFTYPE_AP:
		return mwifiex_send_cmd(priv, HostCmd_CMD_UAP_BSS_STOP,
					HostCmd_ACT_GEN_SET, 0, NULL, true);
	default:
		break;
	}

	return ret;
}