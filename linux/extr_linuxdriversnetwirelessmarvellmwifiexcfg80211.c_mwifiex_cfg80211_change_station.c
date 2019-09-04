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
struct wiphy {int dummy; } ;
struct station_parameters {int sta_flags_set; } ;
struct net_device {int dummy; } ;
struct mwifiex_private {scalar_t__ bss_type; struct station_parameters* sta_params; int /*<<< orphan*/  media_connected; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ENOTSUPP ; 
 scalar_t__ MWIFIEX_BSS_TYPE_STA ; 
 int /*<<< orphan*/  MWIFIEX_TDLS_CONFIG_LINK ; 
 int /*<<< orphan*/  NL80211_STA_FLAG_TDLS_PEER ; 
 struct mwifiex_private* mwifiex_netdev_get_priv (struct net_device*) ; 
 int mwifiex_tdls_oper (struct mwifiex_private*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mwifiex_cfg80211_change_station(struct wiphy *wiphy, struct net_device *dev,
				const u8 *mac,
				struct station_parameters *params)
{
	int ret;
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(dev);

	/* we support change_station handler only for TDLS peers*/
	if (!(params->sta_flags_set & BIT(NL80211_STA_FLAG_TDLS_PEER)))
		return -ENOTSUPP;

	/* make sure we are in station mode and connected */
	if ((priv->bss_type != MWIFIEX_BSS_TYPE_STA) || !priv->media_connected)
		return -ENOTSUPP;

	priv->sta_params = params;

	ret = mwifiex_tdls_oper(priv, mac, MWIFIEX_TDLS_CONFIG_LINK);
	priv->sta_params = NULL;

	return ret;
}