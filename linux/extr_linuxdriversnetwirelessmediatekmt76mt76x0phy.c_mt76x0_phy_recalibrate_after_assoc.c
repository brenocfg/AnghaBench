#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_5__ {TYPE_1__* chan; } ;
struct TYPE_6__ {TYPE_2__ chandef; } ;
struct mt76x0_dev {TYPE_3__ mt76; } ;
struct TYPE_4__ {scalar_t__ band; int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCU_CAL_LC ; 
 int /*<<< orphan*/  MCU_CAL_LOFT ; 
 int /*<<< orphan*/  MCU_CAL_R ; 
 int /*<<< orphan*/  MCU_CAL_RXDCOC ; 
 int /*<<< orphan*/  MCU_CAL_RXIQ ; 
 int /*<<< orphan*/  MCU_CAL_RX_GROUP_DELAY ; 
 int /*<<< orphan*/  MCU_CAL_TXIQ ; 
 int /*<<< orphan*/  MCU_CAL_TX_GROUP_DELAY ; 
 int MT_TX_ALC_CFG_0 ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mt76_rr (struct mt76x0_dev*,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,int,int) ; 
 int /*<<< orphan*/  mt76x0_mcu_calibrate (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x0_vco_cal (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void mt76x0_phy_recalibrate_after_assoc(struct mt76x0_dev *dev)
{
	u32 tx_alc, reg_val;
	u8 channel = dev->mt76.chandef.chan->hw_value;
	int is_5ghz = (dev->mt76.chandef.chan->band == NL80211_BAND_5GHZ) ? 1 : 0;

	mt76x0_mcu_calibrate(dev, MCU_CAL_R, 0);

	mt76x0_vco_cal(dev, channel);

	tx_alc = mt76_rr(dev, MT_TX_ALC_CFG_0);
	mt76_wr(dev, MT_TX_ALC_CFG_0, 0);
	usleep_range(500, 700);

	reg_val = mt76_rr(dev, 0x2124);
	reg_val &= 0xffffff7e;
	mt76_wr(dev, 0x2124, reg_val);

	mt76x0_mcu_calibrate(dev, MCU_CAL_RXDCOC, 0);

	mt76x0_mcu_calibrate(dev, MCU_CAL_LC, is_5ghz);
	mt76x0_mcu_calibrate(dev, MCU_CAL_LOFT, is_5ghz);
	mt76x0_mcu_calibrate(dev, MCU_CAL_TXIQ, is_5ghz);
	mt76x0_mcu_calibrate(dev, MCU_CAL_TX_GROUP_DELAY, is_5ghz);
	mt76x0_mcu_calibrate(dev, MCU_CAL_RXIQ, is_5ghz);
	mt76x0_mcu_calibrate(dev, MCU_CAL_RX_GROUP_DELAY, is_5ghz);

	mt76_wr(dev, 0x2124, reg_val);
	mt76_wr(dev, MT_TX_ALC_CFG_0, tx_alc);
	msleep(100);

	mt76x0_mcu_calibrate(dev, MCU_CAL_RXDCOC, 1);
}