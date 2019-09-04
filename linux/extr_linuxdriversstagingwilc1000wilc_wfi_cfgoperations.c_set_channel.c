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
typedef  int /*<<< orphan*/  u32 ;
struct wiphy {int dummy; } ;
struct wilc_vif {int dummy; } ;
struct wilc_priv {int /*<<< orphan*/  dev; } ;
struct cfg80211_chan_def {TYPE_1__* chan; } ;
struct TYPE_2__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  curr_channel ; 
 int /*<<< orphan*/  ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 int wilc_set_mac_chnl_num (struct wilc_vif*,int /*<<< orphan*/ ) ; 
 struct wilc_priv* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int set_channel(struct wiphy *wiphy,
		       struct cfg80211_chan_def *chandef)
{
	u32 channelnum = 0;
	struct wilc_priv *priv = wiphy_priv(wiphy);
	struct wilc_vif *vif = netdev_priv(priv->dev);
	int result = 0;

	channelnum = ieee80211_frequency_to_channel(chandef->chan->center_freq);

	curr_channel = channelnum;
	result = wilc_set_mac_chnl_num(vif, channelnum);

	if (result != 0)
		netdev_err(priv->dev, "Error in setting channel\n");

	return result;
}