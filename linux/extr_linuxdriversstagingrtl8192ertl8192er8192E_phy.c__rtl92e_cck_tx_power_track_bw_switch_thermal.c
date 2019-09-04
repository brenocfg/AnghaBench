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
struct r8192_priv {int bcck_in_ch14; int CurrentChannelBW; int Record_CCK_20Mindex; int CCK_index; int Record_CCK_40Mindex; TYPE_2__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int channel; } ;
struct TYPE_4__ {TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
#define  HT_CHANNEL_WIDTH_20 129 
#define  HT_CHANNEL_WIDTH_20_40 128 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rtl92e_dm_cck_txpower_adjust (struct net_device*,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_cck_tx_power_track_bw_switch_thermal(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	if (priv->rtllib->current_network.channel == 14 &&
	    !priv->bcck_in_ch14)
		priv->bcck_in_ch14 = true;
	else if (priv->rtllib->current_network.channel != 14 &&
		 priv->bcck_in_ch14)
		priv->bcck_in_ch14 = false;

	switch (priv->CurrentChannelBW) {
	case HT_CHANNEL_WIDTH_20:
		if (priv->Record_CCK_20Mindex == 0)
			priv->Record_CCK_20Mindex = 6;
		priv->CCK_index = priv->Record_CCK_20Mindex;
		RT_TRACE(COMP_POWER_TRACKING,
			 "20MHz, _rtl92e_cck_tx_power_track_bw_switch_thermal(),CCK_index = %d\n",
			 priv->CCK_index);
	break;

	case HT_CHANNEL_WIDTH_20_40:
		priv->CCK_index = priv->Record_CCK_40Mindex;
		RT_TRACE(COMP_POWER_TRACKING,
			 "40MHz, _rtl92e_cck_tx_power_track_bw_switch_thermal(), CCK_index = %d\n",
			 priv->CCK_index);
	break;
	}
	rtl92e_dm_cck_txpower_adjust(dev, priv->bcck_in_ch14);
}