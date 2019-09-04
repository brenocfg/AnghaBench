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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct mt76x0_dev {TYPE_1__* ee; } ;
struct mt76_reg_pair {scalar_t__ reg; int /*<<< orphan*/  value; } ;
struct mt76x0_bbp_switch_item {int bw_band; struct mt76_reg_pair reg_pair; } ;
struct TYPE_2__ {int* lna_gain_5ghz; int lna_gain_2ghz; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC ; 
 int ARRAY_SIZE (struct mt76x0_bbp_switch_item*) ; 
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_BBP_AGC_GAIN ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct mt76x0_bbp_switch_item* mt76x0_bbp_switch_tab ; 

__attribute__((used)) static void
mt76x0_phy_set_chan_bbp_params(struct mt76x0_dev *dev, u8 channel, u16 rf_bw_band)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(mt76x0_bbp_switch_tab); i++) {
		const struct mt76x0_bbp_switch_item *item = &mt76x0_bbp_switch_tab[i];
		const struct mt76_reg_pair *pair = &item->reg_pair;

		if ((rf_bw_band & item->bw_band) != rf_bw_band)
			continue;

		if (pair->reg == MT_BBP(AGC, 8)) {
			u32 val = pair->value;
			u8 gain = FIELD_GET(MT_BBP_AGC_GAIN, val);

			if (channel > 14) {
				if (channel < 100)
					gain -= dev->ee->lna_gain_5ghz[0]*2;
				else if (channel < 137)
					gain -= dev->ee->lna_gain_5ghz[1]*2;
				else
					gain -= dev->ee->lna_gain_5ghz[2]*2;

			} else {
				gain -= dev->ee->lna_gain_2ghz*2;
			}

			val &= ~MT_BBP_AGC_GAIN;
			val |= FIELD_PREP(MT_BBP_AGC_GAIN, gain);
			mt76_wr(dev, pair->reg, val);
		} else {
			mt76_wr(dev, pair->reg, pair->value);
		}
	}
}