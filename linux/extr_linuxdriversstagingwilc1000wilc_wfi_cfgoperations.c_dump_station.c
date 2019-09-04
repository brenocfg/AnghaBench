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
struct wilc_vif {int dummy; } ;
struct wilc_priv {int /*<<< orphan*/  associated_bss; int /*<<< orphan*/  dev; } ;
struct station_info {int /*<<< orphan*/  signal; int /*<<< orphan*/  filled; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NL80211_STA_INFO_SIGNAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wilc_get_rssi (struct wilc_vif*,int /*<<< orphan*/ *) ; 
 struct wilc_priv* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int dump_station(struct wiphy *wiphy, struct net_device *dev,
			int idx, u8 *mac, struct station_info *sinfo)
{
	struct wilc_priv *priv = wiphy_priv(wiphy);
	struct wilc_vif *vif = netdev_priv(priv->dev);

	if (idx != 0)
		return -ENOENT;

	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);

	wilc_get_rssi(vif, &sinfo->signal);

	memcpy(mac, priv->associated_bss, ETH_ALEN);
	return 0;
}