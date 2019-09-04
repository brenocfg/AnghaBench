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
struct ieee80211_vif {int dummy; } ;
struct TYPE_2__ {int ampdu_density; int ampdu_factor; scalar_t__ ht_supported; } ;
struct ieee80211_sta {TYPE_1__ ht_cap; scalar_t__ drv_priv; } ;
struct ieee80211_hw {int dummy; } ;
struct carl9170_sta_info {int ampdu_max_len; int ht_sta; int /*<<< orphan*/ * agg; int /*<<< orphan*/  pending_frames; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int carl9170_op_sta_add(struct ieee80211_hw *hw,
			       struct ieee80211_vif *vif,
			       struct ieee80211_sta *sta)
{
	struct carl9170_sta_info *sta_info = (void *) sta->drv_priv;
	unsigned int i;

	atomic_set(&sta_info->pending_frames, 0);

	if (sta->ht_cap.ht_supported) {
		if (sta->ht_cap.ampdu_density > 6) {
			/*
			 * HW does support 16us AMPDU density.
			 * No HT-Xmit for station.
			 */

			return 0;
		}

		for (i = 0; i < ARRAY_SIZE(sta_info->agg); i++)
			RCU_INIT_POINTER(sta_info->agg[i], NULL);

		sta_info->ampdu_max_len = 1 << (3 + sta->ht_cap.ampdu_factor);
		sta_info->ht_sta = true;
	}

	return 0;
}