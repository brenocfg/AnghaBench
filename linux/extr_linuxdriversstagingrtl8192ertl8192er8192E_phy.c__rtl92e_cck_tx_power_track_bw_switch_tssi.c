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
struct r8192_priv {int CurrentChannelBW; int bcck_in_ch14; TYPE_2__* rtllib; scalar_t__ CCKPresentAttentuation; scalar_t__ CCKPresentAttentuation_difference; scalar_t__ CCKPresentAttentuation_40Mdefault; scalar_t__ CCKPresentAttentuation_20Mdefault; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int channel; } ;
struct TYPE_4__ {TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCKTxBBGainTableLength ; 
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
#define  HT_CHANNEL_WIDTH_20 129 
#define  HT_CHANNEL_WIDTH_20_40 128 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  rtl92e_dm_cck_txpower_adjust (struct net_device*,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_cck_tx_power_track_bw_switch_tssi(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	switch (priv->CurrentChannelBW) {
	case HT_CHANNEL_WIDTH_20:
		priv->CCKPresentAttentuation =
			priv->CCKPresentAttentuation_20Mdefault +
			    priv->CCKPresentAttentuation_difference;

		if (priv->CCKPresentAttentuation >
		    (CCKTxBBGainTableLength-1))
			priv->CCKPresentAttentuation =
					 CCKTxBBGainTableLength-1;
		if (priv->CCKPresentAttentuation < 0)
			priv->CCKPresentAttentuation = 0;

		RT_TRACE(COMP_POWER_TRACKING,
			 "20M, priv->CCKPresentAttentuation = %d\n",
			 priv->CCKPresentAttentuation);

		if (priv->rtllib->current_network.channel == 14 &&
		    !priv->bcck_in_ch14) {
			priv->bcck_in_ch14 = true;
			rtl92e_dm_cck_txpower_adjust(dev, priv->bcck_in_ch14);
		} else if (priv->rtllib->current_network.channel !=
			   14 && priv->bcck_in_ch14) {
			priv->bcck_in_ch14 = false;
			rtl92e_dm_cck_txpower_adjust(dev, priv->bcck_in_ch14);
		} else {
			rtl92e_dm_cck_txpower_adjust(dev, priv->bcck_in_ch14);
		}
		break;

	case HT_CHANNEL_WIDTH_20_40:
		priv->CCKPresentAttentuation =
			priv->CCKPresentAttentuation_40Mdefault +
			priv->CCKPresentAttentuation_difference;

		RT_TRACE(COMP_POWER_TRACKING,
			 "40M, priv->CCKPresentAttentuation = %d\n",
			 priv->CCKPresentAttentuation);
		if (priv->CCKPresentAttentuation >
		    (CCKTxBBGainTableLength - 1))
			priv->CCKPresentAttentuation =
					 CCKTxBBGainTableLength-1;
		if (priv->CCKPresentAttentuation < 0)
			priv->CCKPresentAttentuation = 0;

		if (priv->rtllib->current_network.channel == 14 &&
		    !priv->bcck_in_ch14) {
			priv->bcck_in_ch14 = true;
			rtl92e_dm_cck_txpower_adjust(dev, priv->bcck_in_ch14);
		} else if (priv->rtllib->current_network.channel != 14
			   && priv->bcck_in_ch14) {
			priv->bcck_in_ch14 = false;
			rtl92e_dm_cck_txpower_adjust(dev, priv->bcck_in_ch14);
		} else {
			rtl92e_dm_cck_txpower_adjust(dev, priv->bcck_in_ch14);
		}
		break;
	}
}