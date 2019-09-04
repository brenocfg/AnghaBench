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
struct TYPE_2__ {scalar_t__ ht_supported; } ;
struct ieee80211_sta {TYPE_1__ ht_cap; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ar9170* priv; } ;
struct carl9170_sta_tid {scalar_t__ state; } ;
struct carl9170_sta_info {int ht_sta; int /*<<< orphan*/ * agg; } ;
struct ar9170 {int /*<<< orphan*/  tx_ampdu_list_lock; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ CARL9170_TID_STATE_SHUTDOWN ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carl9170_ampdu_gc (struct ar9170*) ; 
 struct carl9170_sta_tid* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int carl9170_op_sta_remove(struct ieee80211_hw *hw,
				struct ieee80211_vif *vif,
				struct ieee80211_sta *sta)
{
	struct ar9170 *ar = hw->priv;
	struct carl9170_sta_info *sta_info = (void *) sta->drv_priv;
	unsigned int i;
	bool cleanup = false;

	if (sta->ht_cap.ht_supported) {

		sta_info->ht_sta = false;

		rcu_read_lock();
		for (i = 0; i < ARRAY_SIZE(sta_info->agg); i++) {
			struct carl9170_sta_tid *tid_info;

			tid_info = rcu_dereference(sta_info->agg[i]);
			RCU_INIT_POINTER(sta_info->agg[i], NULL);

			if (!tid_info)
				continue;

			spin_lock_bh(&ar->tx_ampdu_list_lock);
			if (tid_info->state > CARL9170_TID_STATE_SHUTDOWN)
				tid_info->state = CARL9170_TID_STATE_SHUTDOWN;
			spin_unlock_bh(&ar->tx_ampdu_list_lock);
			cleanup = true;
		}
		rcu_read_unlock();

		if (cleanup)
			carl9170_ampdu_gc(ar);
	}

	return 0;
}