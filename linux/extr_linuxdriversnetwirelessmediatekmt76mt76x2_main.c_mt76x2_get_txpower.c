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
struct mt76x2_dev {int txpower_cur; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct mt76x2_dev* priv; } ;

/* Variables and functions */

__attribute__((used)) static int
mt76x2_get_txpower(struct ieee80211_hw *hw, struct ieee80211_vif *vif, int *dbm)
{
	struct mt76x2_dev *dev = hw->priv;

	*dbm = dev->txpower_cur / 2;

	/* convert from per-chain power to combined output on 2x2 devices */
	*dbm += 3;

	return 0;
}