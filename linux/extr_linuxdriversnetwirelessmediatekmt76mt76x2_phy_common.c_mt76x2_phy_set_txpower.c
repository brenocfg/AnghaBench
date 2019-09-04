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
struct mt76x2_tx_power_info {int delta_bw40; int delta_bw80; TYPE_3__* chain; } ;
struct mt76_rate_power {int /*<<< orphan*/ * vht; int /*<<< orphan*/ * ht; int /*<<< orphan*/ * ofdm; int /*<<< orphan*/ * cck; } ;
struct TYPE_4__ {int width; struct ieee80211_channel* chan; } ;
struct TYPE_5__ {TYPE_1__ chandef; } ;
struct mt76x2_dev {int target_power; int* target_power_delta; struct mt76_rate_power rate_power; int /*<<< orphan*/  txpower_cur; int /*<<< orphan*/  txpower_conf; TYPE_2__ mt76; } ;
struct ieee80211_channel {int dummy; } ;
typedef  enum nl80211_chan_width { ____Placeholder_nl80211_chan_width } nl80211_chan_width ;
struct TYPE_6__ {int target_power; int delta; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_TX_ALC_CFG_0 ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_0_CH_INIT_0 ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_0_CH_INIT_1 ; 
 int /*<<< orphan*/  MT_TX_PWR_CFG_0 ; 
 int /*<<< orphan*/  MT_TX_PWR_CFG_1 ; 
 int /*<<< orphan*/  MT_TX_PWR_CFG_2 ; 
 int /*<<< orphan*/  MT_TX_PWR_CFG_3 ; 
 int /*<<< orphan*/  MT_TX_PWR_CFG_4 ; 
 int /*<<< orphan*/  MT_TX_PWR_CFG_7 ; 
 int /*<<< orphan*/  MT_TX_PWR_CFG_8 ; 
 int /*<<< orphan*/  MT_TX_PWR_CFG_9 ; 
 int NL80211_CHAN_WIDTH_40 ; 
 int NL80211_CHAN_WIDTH_80 ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2_add_rate_power_offset (struct mt76_rate_power*,int) ; 
 int /*<<< orphan*/  mt76x2_get_max_rate_power (struct mt76_rate_power*) ; 
 int mt76x2_get_min_rate_power (struct mt76_rate_power*) ; 
 int /*<<< orphan*/  mt76x2_get_power_info (struct mt76x2_dev*,struct mt76x2_tx_power_info*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  mt76x2_get_rate_power (struct mt76x2_dev*,struct mt76_rate_power*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  mt76x2_limit_rate_power (struct mt76_rate_power*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2_tx_power_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mt76x2_phy_set_txpower(struct mt76x2_dev *dev)
{
	enum nl80211_chan_width width = dev->mt76.chandef.width;
	struct ieee80211_channel *chan = dev->mt76.chandef.chan;
	struct mt76x2_tx_power_info txp;
	int txp_0, txp_1, delta = 0;
	struct mt76_rate_power t = {};
	int base_power, gain;

	mt76x2_get_power_info(dev, &txp, chan);

	if (width == NL80211_CHAN_WIDTH_40)
		delta = txp.delta_bw40;
	else if (width == NL80211_CHAN_WIDTH_80)
		delta = txp.delta_bw80;

	mt76x2_get_rate_power(dev, &t, chan);
	mt76x2_add_rate_power_offset(&t, txp.chain[0].target_power);
	mt76x2_limit_rate_power(&t, dev->txpower_conf);
	dev->txpower_cur = mt76x2_get_max_rate_power(&t);

	base_power = mt76x2_get_min_rate_power(&t);
	delta += base_power - txp.chain[0].target_power;
	txp_0 = txp.chain[0].target_power + txp.chain[0].delta + delta;
	txp_1 = txp.chain[1].target_power + txp.chain[1].delta + delta;

	gain = min(txp_0, txp_1);
	if (gain < 0) {
		base_power -= gain;
		txp_0 -= gain;
		txp_1 -= gain;
	} else if (gain > 0x2f) {
		base_power -= gain - 0x2f;
		txp_0 = 0x2f;
		txp_1 = 0x2f;
	}

	mt76x2_add_rate_power_offset(&t, -base_power);
	dev->target_power = txp.chain[0].target_power;
	dev->target_power_delta[0] = txp_0 - txp.chain[0].target_power;
	dev->target_power_delta[1] = txp_1 - txp.chain[0].target_power;
	dev->rate_power = t;

	mt76_rmw_field(dev, MT_TX_ALC_CFG_0, MT_TX_ALC_CFG_0_CH_INIT_0, txp_0);
	mt76_rmw_field(dev, MT_TX_ALC_CFG_0, MT_TX_ALC_CFG_0_CH_INIT_1, txp_1);

	mt76_wr(dev, MT_TX_PWR_CFG_0,
		mt76x2_tx_power_mask(t.cck[0], t.cck[2], t.ofdm[0], t.ofdm[2]));
	mt76_wr(dev, MT_TX_PWR_CFG_1,
		mt76x2_tx_power_mask(t.ofdm[4], t.ofdm[6], t.ht[0], t.ht[2]));
	mt76_wr(dev, MT_TX_PWR_CFG_2,
		mt76x2_tx_power_mask(t.ht[4], t.ht[6], t.ht[8], t.ht[10]));
	mt76_wr(dev, MT_TX_PWR_CFG_3,
		mt76x2_tx_power_mask(t.ht[12], t.ht[14], t.ht[0], t.ht[2]));
	mt76_wr(dev, MT_TX_PWR_CFG_4,
		mt76x2_tx_power_mask(t.ht[4], t.ht[6], 0, 0));
	mt76_wr(dev, MT_TX_PWR_CFG_7,
		mt76x2_tx_power_mask(t.ofdm[6], t.vht[8], t.ht[6], t.vht[8]));
	mt76_wr(dev, MT_TX_PWR_CFG_8,
		mt76x2_tx_power_mask(t.ht[14], t.vht[8], t.vht[8], 0));
	mt76_wr(dev, MT_TX_PWR_CFG_9,
		mt76x2_tx_power_mask(t.ht[6], t.vht[8], t.vht[8], 0));
}