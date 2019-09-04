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
struct mt76x0_dev {int /*<<< orphan*/  vif_mask; } ;
struct TYPE_2__ {int hw_key_idx; int /*<<< orphan*/  idx; } ;
struct mt76_vif {unsigned int idx; TYPE_1__ group_wcid; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct mt76x0_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GROUP_WCID (unsigned int) ; 
 unsigned int ffs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt76x0_add_interface(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif)
{
	struct mt76x0_dev *dev = hw->priv;
	struct mt76_vif *mvif = (struct mt76_vif *) vif->drv_priv;
	unsigned int idx;

	idx = ffs(~dev->vif_mask);
	if (!idx || idx > 8)
		return -ENOSPC;

	idx--;
	dev->vif_mask |= BIT(idx);

	mvif->idx = idx;
	mvif->group_wcid.idx = GROUP_WCID(idx);
	mvif->group_wcid.hw_key_idx = -1;

	return 0;
}