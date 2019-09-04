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
typedef  void* u8 ;
typedef  int u32 ;
struct TYPE_6__ {void** agc_gain_init; scalar_t__ avg_rssi_all; int low_gain; void** agc_gain_cur; void* agc_gain_adjust; } ;
struct TYPE_4__ {scalar_t__ width; } ;
struct TYPE_5__ {TYPE_1__ chandef; } ;
struct mt76x2_dev {TYPE_3__ cal; TYPE_2__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_RX_STAT_1 ; 
 scalar_t__ NL80211_CHAN_WIDTH_80 ; 
 int /*<<< orphan*/  RXO ; 
 int mt76_rr (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x2_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mt76x2_get_low_rssi_gain_thresh (struct mt76x2_dev*) ; 
 scalar_t__ mt76x2_get_rssi_gain_thresh (struct mt76x2_dev*) ; 
 scalar_t__ mt76x2_has_ext_lna (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2_phy_adjust_vga_gain (struct mt76x2_dev*) ; 
 scalar_t__ mt76x2_phy_get_min_avg_rssi (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2_phy_set_gain_val (struct mt76x2_dev*) ; 

__attribute__((used)) static void
mt76x2_phy_update_channel_gain(struct mt76x2_dev *dev)
{
	u8 *gain = dev->cal.agc_gain_init;
	u8 low_gain_delta, gain_delta;
	bool gain_change;
	int low_gain;
	u32 val;

	dev->cal.avg_rssi_all = mt76x2_phy_get_min_avg_rssi(dev);

	low_gain = (dev->cal.avg_rssi_all > mt76x2_get_rssi_gain_thresh(dev)) +
		   (dev->cal.avg_rssi_all > mt76x2_get_low_rssi_gain_thresh(dev));

	gain_change = (dev->cal.low_gain & 2) ^ (low_gain & 2);
	dev->cal.low_gain = low_gain;

	if (!gain_change) {
		mt76x2_phy_adjust_vga_gain(dev);
		return;
	}

	if (dev->mt76.chandef.width == NL80211_CHAN_WIDTH_80) {
		mt76_wr(dev, MT_BBP(RXO, 14), 0x00560211);
		val = mt76_rr(dev, MT_BBP(AGC, 26)) & ~0xf;
		if (low_gain == 2)
			val |= 0x3;
		else
			val |= 0x5;
		mt76_wr(dev, MT_BBP(AGC, 26), val);
	} else {
		mt76_wr(dev, MT_BBP(RXO, 14), 0x00560423);
	}

	if (mt76x2_has_ext_lna(dev))
		low_gain_delta = 10;
	else
		low_gain_delta = 14;

	if (low_gain == 2) {
		mt76_wr(dev, MT_BBP(RXO, 18), 0xf000a990);
		mt76_wr(dev, MT_BBP(AGC, 35), 0x08080808);
		mt76_wr(dev, MT_BBP(AGC, 37), 0x08080808);
		gain_delta = low_gain_delta;
		dev->cal.agc_gain_adjust = 0;
	} else {
		mt76_wr(dev, MT_BBP(RXO, 18), 0xf000a991);
		if (dev->mt76.chandef.width == NL80211_CHAN_WIDTH_80)
			mt76_wr(dev, MT_BBP(AGC, 35), 0x10101014);
		else
			mt76_wr(dev, MT_BBP(AGC, 35), 0x11111116);
		mt76_wr(dev, MT_BBP(AGC, 37), 0x2121262C);
		gain_delta = 0;
		dev->cal.agc_gain_adjust = low_gain_delta;
	}

	dev->cal.agc_gain_cur[0] = gain[0] - gain_delta;
	dev->cal.agc_gain_cur[1] = gain[1] - gain_delta;
	mt76x2_phy_set_gain_val(dev);

	/* clear false CCA counters */
	mt76_rr(dev, MT_RX_STAT_1);
}