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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct r8192_priv {scalar_t__ undecorated_smoothed_pwdb; scalar_t__ reset_count; scalar_t__ CurrentChannelBW; TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int dig_enable_flag; scalar_t__ dig_state; scalar_t__ rssi_low_thresh; scalar_t__ rssi_high_thresh; void* dig_highpwr_state; scalar_t__ dig_algorithm_switch; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 void* DM_STA_DIG_MAX ; 
 scalar_t__ DM_STA_DIG_OFF ; 
 scalar_t__ DM_STA_DIG_ON ; 
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 scalar_t__ RTLLIB_LINKED ; 
 int /*<<< orphan*/  UFWP ; 
 int /*<<< orphan*/  _rtl92e_dm_ctrl_initgain_byrssi_highpwr (struct net_device*) ; 
 int /*<<< orphan*/  bMaskByte1 ; 
 TYPE_2__ dm_digtable ; 
 int rOFDM0_RxDetector1 ; 
 int rOFDM0_XAAGCCore1 ; 
 int rOFDM0_XATxAFE ; 
 int rOFDM0_XBAGCCore1 ; 
 int rOFDM0_XCAGCCore1 ; 
 int rOFDM0_XDAGCCore1 ; 
 int /*<<< orphan*/  rtl92e_set_bb_reg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl92e_writeb (struct net_device*,int,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_ctrl_initgain_byrssi_false_alarm(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	static u32 reset_cnt;
	u8 i;

	if (dm_digtable.dig_enable_flag == false)
		return;

	if (dm_digtable.dig_algorithm_switch) {
		dm_digtable.dig_state = DM_STA_DIG_MAX;
		for (i = 0; i < 3; i++)
			rtl92e_set_bb_reg(dev, UFWP, bMaskByte1, 0x1);
		dm_digtable.dig_algorithm_switch = 0;
	}

	if (priv->rtllib->state != RTLLIB_LINKED)
		return;

	if ((priv->undecorated_smoothed_pwdb > dm_digtable.rssi_low_thresh) &&
		(priv->undecorated_smoothed_pwdb < dm_digtable.rssi_high_thresh))
		return;
	if (priv->undecorated_smoothed_pwdb <= dm_digtable.rssi_low_thresh) {
		if (dm_digtable.dig_state == DM_STA_DIG_OFF &&
			(priv->reset_count == reset_cnt))
			return;
		reset_cnt = priv->reset_count;

		dm_digtable.dig_highpwr_state = DM_STA_DIG_MAX;
		dm_digtable.dig_state = DM_STA_DIG_OFF;

		rtl92e_set_bb_reg(dev, UFWP, bMaskByte1, 0x8);

		rtl92e_writeb(dev, rOFDM0_XAAGCCore1, 0x17);
		rtl92e_writeb(dev, rOFDM0_XBAGCCore1, 0x17);
		rtl92e_writeb(dev, rOFDM0_XCAGCCore1, 0x17);
		rtl92e_writeb(dev, rOFDM0_XDAGCCore1, 0x17);

		if (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
			rtl92e_writeb(dev, (rOFDM0_XATxAFE+3), 0x00);
		else
			rtl92e_writeb(dev, rOFDM0_RxDetector1, 0x42);

		rtl92e_writeb(dev, 0xa0a, 0x08);

		return;
	}

	if (priv->undecorated_smoothed_pwdb >= dm_digtable.rssi_high_thresh) {
		u8 reset_flag = 0;

		if (dm_digtable.dig_state == DM_STA_DIG_ON &&
		    (priv->reset_count == reset_cnt)) {
			_rtl92e_dm_ctrl_initgain_byrssi_highpwr(dev);
			return;
		}
		if (priv->reset_count != reset_cnt)
			reset_flag = 1;

		reset_cnt = priv->reset_count;

		dm_digtable.dig_state = DM_STA_DIG_ON;

		if (reset_flag == 1) {
			rtl92e_writeb(dev, rOFDM0_XAAGCCore1, 0x2c);
			rtl92e_writeb(dev, rOFDM0_XBAGCCore1, 0x2c);
			rtl92e_writeb(dev, rOFDM0_XCAGCCore1, 0x2c);
			rtl92e_writeb(dev, rOFDM0_XDAGCCore1, 0x2c);
		} else {
			rtl92e_writeb(dev, rOFDM0_XAAGCCore1, 0x20);
			rtl92e_writeb(dev, rOFDM0_XBAGCCore1, 0x20);
			rtl92e_writeb(dev, rOFDM0_XCAGCCore1, 0x20);
			rtl92e_writeb(dev, rOFDM0_XDAGCCore1, 0x20);
		}

		if (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
			rtl92e_writeb(dev, (rOFDM0_XATxAFE+3), 0x20);
		else
			rtl92e_writeb(dev, rOFDM0_RxDetector1, 0x44);

		rtl92e_writeb(dev, 0xa0a, 0xcd);

		rtl92e_set_bb_reg(dev, UFWP, bMaskByte1, 0x1);
	}
	_rtl92e_dm_ctrl_initgain_byrssi_highpwr(dev);
}