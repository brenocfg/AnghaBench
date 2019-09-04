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
struct ieee80211_hw {struct ath10k* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  timeout; } ;
struct ath10k {TYPE_1__ scan; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_scan_abort (struct ath10k*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_cancel_hw_scan(struct ieee80211_hw *hw,
				  struct ieee80211_vif *vif)
{
	struct ath10k *ar = hw->priv;

	mutex_lock(&ar->conf_mutex);
	ath10k_scan_abort(ar);
	mutex_unlock(&ar->conf_mutex);

	cancel_delayed_work_sync(&ar->scan.timeout);
}