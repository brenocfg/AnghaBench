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
struct mt76x2_dev {int /*<<< orphan*/  mt76; } ;
struct ieee80211_vif {int /*<<< orphan*/  txq; } ;
struct ieee80211_hw {struct mt76x2_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76_txq_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mt76x2_remove_interface(struct ieee80211_hw *hw,
			     struct ieee80211_vif *vif)
{
	struct mt76x2_dev *dev = hw->priv;

	mt76_txq_remove(&dev->mt76, vif->txq);
}