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
typedef  int /*<<< orphan*/  u32 ;
struct mt7601u_dev {int dummy; } ;
struct ieee80211_hw {struct mt7601u_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_TX_RTS_CFG ; 
 int /*<<< orphan*/  MT_TX_RTS_CFG_THRESH ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt7601u_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7601u_set_rts_threshold(struct ieee80211_hw *hw, u32 value)
{
	struct mt7601u_dev *dev = hw->priv;

	mt76_rmw_field(dev, MT_TX_RTS_CFG, MT_TX_RTS_CFG_THRESH, value);

	return 0;
}