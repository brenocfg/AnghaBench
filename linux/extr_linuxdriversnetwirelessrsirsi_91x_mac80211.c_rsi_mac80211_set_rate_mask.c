#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rsi_hw {struct rsi_common* priv; } ;
struct rsi_common {int* fixedrate_mask; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_6__ {TYPE_1__* chan; } ;
struct TYPE_7__ {TYPE_2__ chandef; } ;
struct ieee80211_hw {TYPE_3__ conf; struct rsi_hw* priv; } ;
struct cfg80211_bitrate_mask {TYPE_4__* control; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_8__ {int legacy; int* ht_mcs; } ;
struct TYPE_5__ {int band; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rsi_mac80211_set_rate_mask(struct ieee80211_hw *hw,
				      struct ieee80211_vif *vif,
				      const struct cfg80211_bitrate_mask *mask)
{
	struct rsi_hw *adapter = hw->priv;
	struct rsi_common *common = adapter->priv;
	enum nl80211_band band = hw->conf.chandef.chan->band;

	mutex_lock(&common->mutex);
	common->fixedrate_mask[band] = 0;

	if (mask->control[band].legacy == 0xfff) {
		common->fixedrate_mask[band] =
			(mask->control[band].ht_mcs[0] << 12);
	} else {
		common->fixedrate_mask[band] =
			mask->control[band].legacy;
	}
	mutex_unlock(&common->mutex);

	return 0;
}