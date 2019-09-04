#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int /*<<< orphan*/  avg_rssi_all; } ;
struct TYPE_6__ {int center_freq1; int width; TYPE_1__* chan; } ;
struct TYPE_7__ {TYPE_2__ chandef; } ;
struct mt76x2_dev {TYPE_4__ cal; TYPE_3__ mt76; } ;
struct TYPE_5__ {int hw_value; int center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_RX_STAT_1 ; 
 int /*<<< orphan*/  MT_RX_STAT_1_CCA_ERRORS ; 
#define  NL80211_CHAN_WIDTH_40 129 
#define  NL80211_CHAN_WIDTH_80 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2_phy_get_min_avg_rssi (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2u_mcu_set_dynamic_vga (struct mt76x2_dev*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt76x2u_phy_update_channel_gain(struct mt76x2_dev *dev)
{
	u8 channel = dev->mt76.chandef.chan->hw_value;
	int freq, freq1;
	u32 false_cca;

	freq = dev->mt76.chandef.chan->center_freq;
	freq1 = dev->mt76.chandef.center_freq1;

	switch (dev->mt76.chandef.width) {
	case NL80211_CHAN_WIDTH_80: {
		int ch_group_index;

		ch_group_index = (freq - freq1 + 30) / 20;
		if (WARN_ON(ch_group_index < 0 || ch_group_index > 3))
			ch_group_index = 0;
		channel += 6 - ch_group_index * 4;
		break;
	}
	case NL80211_CHAN_WIDTH_40:
		if (freq1 > freq)
			channel += 2;
		else
			channel -= 2;
		break;
	default:
		break;
	}

	dev->cal.avg_rssi_all = mt76x2_phy_get_min_avg_rssi(dev);
	false_cca = FIELD_GET(MT_RX_STAT_1_CCA_ERRORS,
			      mt76_rr(dev, MT_RX_STAT_1));

	mt76x2u_mcu_set_dynamic_vga(dev, channel, false, false,
				    dev->cal.avg_rssi_all, false_cca);
}