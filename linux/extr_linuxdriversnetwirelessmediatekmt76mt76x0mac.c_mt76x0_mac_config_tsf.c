#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct mt76x0_dev {int dummy; } ;

/* Variables and functions */
 int FIELD_PREP (int,int) ; 
 int /*<<< orphan*/  MT_BEACON_TIME_CFG ; 
 int MT_BEACON_TIME_CFG_INTVAL ; 
 int MT_BEACON_TIME_CFG_SYNC_MODE ; 
 int MT_BEACON_TIME_CFG_TBTT_EN ; 
 int MT_BEACON_TIME_CFG_TIMER_EN ; 
 int mt76_rr (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 

void mt76x0_mac_config_tsf(struct mt76x0_dev *dev, bool enable, int interval)
{
	u32 val = mt76_rr(dev, MT_BEACON_TIME_CFG);

	val &= ~(MT_BEACON_TIME_CFG_TIMER_EN |
		 MT_BEACON_TIME_CFG_SYNC_MODE |
		 MT_BEACON_TIME_CFG_TBTT_EN);

	if (!enable) {
		mt76_wr(dev, MT_BEACON_TIME_CFG, val);
		return;
	}

	val &= ~MT_BEACON_TIME_CFG_INTVAL;
	val |= FIELD_PREP(MT_BEACON_TIME_CFG_INTVAL, interval << 4) |
		MT_BEACON_TIME_CFG_TIMER_EN |
		MT_BEACON_TIME_CFG_SYNC_MODE |
		MT_BEACON_TIME_CFG_TBTT_EN;
}