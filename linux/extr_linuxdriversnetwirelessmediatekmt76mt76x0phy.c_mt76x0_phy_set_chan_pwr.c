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
typedef  int const u8 ;
typedef  int u32 ;
struct mt76x0_dev {TYPE_1__* ee; } ;
struct TYPE_2__ {int* tx_pwr_per_chan; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_0 ; 
 scalar_t__ WARN_ON (int) ; 
 int mt76_rr (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mt76x0_phy_set_chan_pwr(struct mt76x0_dev *dev, u8 channel)
{
	static const int mt76x0_tx_pwr_ch_list[] = {
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,
		36,38,40,44,46,48,52,54,56,60,62,64,
		100,102,104,108,110,112,116,118,120,124,126,128,132,134,136,140,
		149,151,153,157,159,161,165,167,169,171,173,
		42,58,106,122,155
	};
	int i;
	u32 val;

	for (i = 0; i < ARRAY_SIZE(mt76x0_tx_pwr_ch_list); i++)
		if (mt76x0_tx_pwr_ch_list[i] == channel)
			break;

	if (WARN_ON(i == ARRAY_SIZE(mt76x0_tx_pwr_ch_list)))
		return;

	val = mt76_rr(dev, MT_TX_ALC_CFG_0);
	val &= ~0x3f3f;
	val |= dev->ee->tx_pwr_per_chan[i];
	val |= 0x2f2f << 16;
	mt76_wr(dev, MT_TX_ALC_CFG_0, val);
}