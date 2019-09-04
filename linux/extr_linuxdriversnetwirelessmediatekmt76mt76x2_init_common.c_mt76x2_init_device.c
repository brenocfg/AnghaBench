#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct mt76x2_vif {int dummy; } ;
struct mt76x2_sta {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  cap; } ;
struct TYPE_13__ {TYPE_4__ ht_cap; } ;
struct TYPE_14__ {TYPE_5__ sband; } ;
struct TYPE_9__ {int /*<<< orphan*/  cap; } ;
struct TYPE_10__ {TYPE_1__ ht_cap; } ;
struct TYPE_11__ {TYPE_2__ sband; } ;
struct TYPE_16__ {int antenna_mask; TYPE_6__ sband_5g; TYPE_3__ sband_2g; } ;
struct TYPE_15__ {int idx; int hw_key_idx; } ;
struct mt76x2_dev {int chainmask; int slottime; TYPE_8__ mt76; TYPE_7__ global_wcid; } ;
struct ieee80211_hw {int queues; int max_rates; int max_report_rates; int max_rate_tries; int extra_tx_headroom; int sta_data_size; int vif_data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_HT_CAP_LDPC_CODING ; 
 int /*<<< orphan*/  SUPPORTS_HT_CCK_RATES ; 
 int /*<<< orphan*/  SUPPORTS_REORDERING_BUFFER ; 
 int /*<<< orphan*/  ieee80211_hw_set (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 struct ieee80211_hw* mt76_hw (struct mt76x2_dev*) ; 

void mt76x2_init_device(struct mt76x2_dev *dev)
{
	struct ieee80211_hw *hw = mt76_hw(dev);

	hw->queues = 4;
	hw->max_rates = 1;
	hw->max_report_rates = 7;
	hw->max_rate_tries = 1;
	hw->extra_tx_headroom = 2;

	hw->sta_data_size = sizeof(struct mt76x2_sta);
	hw->vif_data_size = sizeof(struct mt76x2_vif);

	ieee80211_hw_set(hw, SUPPORTS_HT_CCK_RATES);
	ieee80211_hw_set(hw, SUPPORTS_REORDERING_BUFFER);

	dev->mt76.sband_2g.sband.ht_cap.cap |= IEEE80211_HT_CAP_LDPC_CODING;
	dev->mt76.sband_5g.sband.ht_cap.cap |= IEEE80211_HT_CAP_LDPC_CODING;

	dev->chainmask = 0x202;
	dev->global_wcid.idx = 255;
	dev->global_wcid.hw_key_idx = -1;
	dev->slottime = 9;

	/* init antenna configuration */
	dev->mt76.antenna_mask = 3;
}