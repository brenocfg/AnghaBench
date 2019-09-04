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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct cfg80211_chan_def {int center_freq1; int width; TYPE_1__* chan; } ;
struct TYPE_4__ {struct cfg80211_chan_def chandef; int /*<<< orphan*/  state; } ;
struct mt76x0_dev {TYPE_2__ mt76; } ;
struct TYPE_3__ {int center_freq; int hw_value; int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CORE ; 
 int FIELD_PREP (int,int) ; 
 int /*<<< orphan*/  MCU_CAL_RXDCOC ; 
 int /*<<< orphan*/  MT76_SCANNING ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_EXT_CCA_CFG ; 
 int MT_EXT_CCA_CFG_CCA0 ; 
 int MT_EXT_CCA_CFG_CCA1 ; 
 int MT_EXT_CCA_CFG_CCA2 ; 
 int MT_EXT_CCA_CFG_CCA3 ; 
 int MT_EXT_CCA_CFG_CCA_MASK ; 
#define  NL80211_CHAN_WIDTH_40 129 
#define  NL80211_CHAN_WIDTH_80 128 
 int /*<<< orphan*/  RF_A_BAND ; 
 int /*<<< orphan*/  RF_BW_20 ; 
 int /*<<< orphan*/  RF_BW_40 ; 
 int /*<<< orphan*/  RF_BW_80 ; 
 int /*<<< orphan*/  RF_G_BAND ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mt76_rmw (struct mt76x0_dev*,int /*<<< orphan*/ ,int,int) ; 
 int mt76_rr (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x0_bbp_set_bw (struct mt76x0_dev*,int) ; 
 int /*<<< orphan*/  mt76x0_bbp_set_ctrlch (struct mt76x0_dev*,int,int) ; 
 int /*<<< orphan*/  mt76x0_mac_set_ctrlch (struct mt76x0_dev*,int) ; 
 int /*<<< orphan*/  mt76x0_mcu_calibrate (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x0_phy_set_band (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x0_phy_set_chan_bbp_params (struct mt76x0_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x0_phy_set_chan_pwr (struct mt76x0_dev*,int) ; 
 int /*<<< orphan*/  mt76x0_phy_set_chan_rf_params (struct mt76x0_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x0_vco_cal (struct mt76x0_dev*,int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
__mt76x0_phy_set_channel(struct mt76x0_dev *dev,
		       struct cfg80211_chan_def *chandef)
{
	u32 ext_cca_chan[4] = {
		[0] = FIELD_PREP(MT_EXT_CCA_CFG_CCA0, 0) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA1, 1) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA2, 2) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA3, 3) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA_MASK, BIT(0)),
		[1] = FIELD_PREP(MT_EXT_CCA_CFG_CCA0, 1) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA1, 0) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA2, 2) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA3, 3) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA_MASK, BIT(1)),
		[2] = FIELD_PREP(MT_EXT_CCA_CFG_CCA0, 2) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA1, 3) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA2, 1) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA3, 0) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA_MASK, BIT(2)),
		[3] = FIELD_PREP(MT_EXT_CCA_CFG_CCA0, 3) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA1, 2) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA2, 1) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA3, 0) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA_MASK, BIT(3)),
	};
	bool scan = test_bit(MT76_SCANNING, &dev->mt76.state);
	int ch_group_index, freq, freq1;
	u8 channel;
	u32 val;
	u16 rf_bw_band;

	freq = chandef->chan->center_freq;
	freq1 = chandef->center_freq1;
	channel = chandef->chan->hw_value;
	rf_bw_band = (channel <= 14) ? RF_G_BAND : RF_A_BAND;

	switch (chandef->width) {
	case NL80211_CHAN_WIDTH_40:
		if (freq1 > freq)
			ch_group_index = 0;
		else
			ch_group_index = 1;
		channel += 2 - ch_group_index * 4;
		rf_bw_band |= RF_BW_40;
		break;
	case NL80211_CHAN_WIDTH_80:
		ch_group_index = (freq - freq1 + 30) / 20;
		if (WARN_ON(ch_group_index < 0 || ch_group_index > 3))
			ch_group_index = 0;
		channel += 6 - ch_group_index * 4;
		rf_bw_band |= RF_BW_80;
		break;
	default:
		ch_group_index = 0;
		rf_bw_band |= RF_BW_20;
		break;
	}

	mt76x0_bbp_set_bw(dev, chandef->width);
	mt76x0_bbp_set_ctrlch(dev, chandef->width, ch_group_index);
	mt76x0_mac_set_ctrlch(dev, ch_group_index & 1);

	mt76_rmw(dev, MT_EXT_CCA_CFG,
		 (MT_EXT_CCA_CFG_CCA0 |
		  MT_EXT_CCA_CFG_CCA1 |
		  MT_EXT_CCA_CFG_CCA2 |
		  MT_EXT_CCA_CFG_CCA3 |
		  MT_EXT_CCA_CFG_CCA_MASK),
		 ext_cca_chan[ch_group_index]);

	mt76x0_phy_set_band(dev, chandef->chan->band);
	mt76x0_phy_set_chan_rf_params(dev, channel, rf_bw_band);

	/* set Japan Tx filter at channel 14 */
	val = mt76_rr(dev, MT_BBP(CORE, 1));
	if (channel == 14)
		val |= 0x20;
	else
		val &= ~0x20;
	mt76_wr(dev, MT_BBP(CORE, 1), val);

	mt76x0_phy_set_chan_bbp_params(dev, channel, rf_bw_band);

	/* Vendor driver don't do it */
	/* mt76x0_phy_set_tx_power(dev, channel, rf_bw_band); */

	mt76x0_vco_cal(dev, channel);
	if (scan)
		mt76x0_mcu_calibrate(dev, MCU_CAL_RXDCOC, 1);

	mt76x0_phy_set_chan_pwr(dev, channel);

	dev->mt76.chandef = *chandef;
	return 0;
}