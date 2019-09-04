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
typedef  scalar_t__ u32 ;
struct r8192_priv {scalar_t__ undecorated_smoothed_pwdb; scalar_t__ reset_count; scalar_t__ CurrentChannelBW; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ rssi_high_power_lowthresh; scalar_t__ rssi_high_power_highthresh; scalar_t__ dig_highpwr_state; scalar_t__ rssi_high_thresh; } ;

/* Variables and functions */
 scalar_t__ DM_STA_DIG_OFF ; 
 scalar_t__ DM_STA_DIG_ON ; 
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 TYPE_1__ dm_digtable ; 
 scalar_t__ rOFDM0_RxDetector1 ; 
 scalar_t__ rOFDM0_XATxAFE ; 
 int /*<<< orphan*/  rtl92e_writeb (struct net_device*,scalar_t__,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_ctrl_initgain_byrssi_highpwr(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	static u32 reset_cnt_highpwr;

	if ((priv->undecorated_smoothed_pwdb >
	     dm_digtable.rssi_high_power_lowthresh) &&
	    (priv->undecorated_smoothed_pwdb <
	     dm_digtable.rssi_high_power_highthresh))
		return;

	if (priv->undecorated_smoothed_pwdb >=
	    dm_digtable.rssi_high_power_highthresh) {
		if (dm_digtable.dig_highpwr_state == DM_STA_DIG_ON &&
			(priv->reset_count == reset_cnt_highpwr))
			return;
		dm_digtable.dig_highpwr_state = DM_STA_DIG_ON;

		if (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
			rtl92e_writeb(dev, (rOFDM0_XATxAFE+3), 0x10);
		else
			rtl92e_writeb(dev, rOFDM0_RxDetector1, 0x43);
	} else {
		if (dm_digtable.dig_highpwr_state == DM_STA_DIG_OFF &&
			(priv->reset_count == reset_cnt_highpwr))
			return;
		dm_digtable.dig_highpwr_state = DM_STA_DIG_OFF;

		if ((priv->undecorated_smoothed_pwdb <
		     dm_digtable.rssi_high_power_lowthresh) &&
		    (priv->undecorated_smoothed_pwdb >=
		    dm_digtable.rssi_high_thresh)) {
			if (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
				rtl92e_writeb(dev, (rOFDM0_XATxAFE+3), 0x20);
			else
				rtl92e_writeb(dev, rOFDM0_RxDetector1, 0x44);
		}
	}
	reset_cnt_highpwr = priv->reset_count;
}