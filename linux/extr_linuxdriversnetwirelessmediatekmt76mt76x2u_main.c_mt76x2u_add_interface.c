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
struct TYPE_3__ {int hw_key_idx; int /*<<< orphan*/  idx; } ;
struct mt76x2_vif {unsigned int idx; TYPE_1__ group_wcid; } ;
struct TYPE_4__ {int /*<<< orphan*/  macaddr; } ;
struct mt76x2_dev {TYPE_2__ mt76; } ;
struct ieee80211_vif {int /*<<< orphan*/  txq; int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct mt76x2_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_VIF_WCID (unsigned int) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2_txq_init (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2u_mac_setaddr (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt76x2u_add_interface(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif)
{
	struct mt76x2_dev *dev = hw->priv;
	struct mt76x2_vif *mvif = (struct mt76x2_vif *)vif->drv_priv;
	unsigned int idx = 0;

	if (!ether_addr_equal(dev->mt76.macaddr, vif->addr))
		mt76x2u_mac_setaddr(dev, vif->addr);

	mvif->idx = idx;
	mvif->group_wcid.idx = MT_VIF_WCID(idx);
	mvif->group_wcid.hw_key_idx = -1;
	mt76x2_txq_init(dev, vif->txq);

	return 0;
}