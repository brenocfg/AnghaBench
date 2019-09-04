#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct wireless_dev {scalar_t__ iftype; } ;
struct wiphy {int dummy; } ;
struct wilc_vif {int /*<<< orphan*/  ndev; } ;
struct TYPE_2__ {unsigned int listen_duration; int /*<<< orphan*/  listen_session_id; int /*<<< orphan*/  listen_cookie; struct ieee80211_channel* listen_ch; } ;
struct wilc_priv {TYPE_1__ remain_on_ch_params; int /*<<< orphan*/  dev; } ;
struct ieee80211_channel {int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  curr_channel ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 int wilc_remain_on_channel (struct wilc_vif*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  wilc_wfi_remain_on_channel_expired ; 
 int /*<<< orphan*/  wilc_wfi_remain_on_channel_ready ; 
 struct wilc_priv* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int remain_on_channel(struct wiphy *wiphy,
			     struct wireless_dev *wdev,
			     struct ieee80211_channel *chan,
			     unsigned int duration, u64 *cookie)
{
	int ret = 0;
	struct wilc_priv *priv = wiphy_priv(wiphy);
	struct wilc_vif *vif = netdev_priv(priv->dev);

	if (wdev->iftype == NL80211_IFTYPE_AP) {
		netdev_dbg(vif->ndev, "Required while in AP mode\n");
		return ret;
	}

	curr_channel = chan->hw_value;

	priv->remain_on_ch_params.listen_ch = chan;
	priv->remain_on_ch_params.listen_cookie = *cookie;
	priv->remain_on_ch_params.listen_duration = duration;
	priv->remain_on_ch_params.listen_session_id++;

	return wilc_remain_on_channel(vif,
				priv->remain_on_ch_params.listen_session_id,
				duration, chan->hw_value,
				wilc_wfi_remain_on_channel_expired,
				wilc_wfi_remain_on_channel_ready, (void *)priv);
}