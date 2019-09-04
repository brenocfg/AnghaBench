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
struct TYPE_4__ {int hw_key_idx; int /*<<< orphan*/  idx; } ;
struct mt76x2_vif {unsigned int idx; TYPE_2__ group_wcid; } ;
struct TYPE_3__ {int* macaddr; } ;
struct mt76x2_dev {TYPE_1__ mt76; } ;
struct ieee80211_vif {int* addr; scalar_t__ type; int /*<<< orphan*/  txq; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct mt76x2_dev* priv; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  MT_VIF_WCID (unsigned int) ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  mt76x2_txq_init (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt76x2_add_interface(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	struct mt76x2_dev *dev = hw->priv;
	struct mt76x2_vif *mvif = (struct mt76x2_vif *) vif->drv_priv;
	unsigned int idx = 0;

	if (vif->addr[0] & BIT(1))
		idx = 1 + (((dev->mt76.macaddr[0] ^ vif->addr[0]) >> 2) & 7);

	/*
	 * Client mode typically only has one configurable BSSID register,
	 * which is used for bssidx=0. This is linked to the MAC address.
	 * Since mac80211 allows changing interface types, and we cannot
	 * force the use of the primary MAC address for a station mode
	 * interface, we need some other way of configuring a per-interface
	 * remote BSSID.
	 * The hardware provides an AP-Client feature, where bssidx 0-7 are
	 * used for AP mode and bssidx 8-15 for client mode.
	 * We shift the station interface bss index by 8 to force the
	 * hardware to recognize the BSSID.
	 * The resulting bssidx mismatch for unicast frames is ignored by hw.
	 */
	if (vif->type == NL80211_IFTYPE_STATION)
		idx += 8;

	mvif->idx = idx;
	mvif->group_wcid.idx = MT_VIF_WCID(idx);
	mvif->group_wcid.hw_key_idx = -1;
	mt76x2_txq_init(dev, vif->txq);

	return 0;
}