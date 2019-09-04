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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_hw {int dummy; } ;
struct ath10k_vif {scalar_t__ vdev_id; int /*<<< orphan*/  connection_loss_work; int /*<<< orphan*/  is_up; struct ath10k* ar; } ;
struct ath10k {struct ieee80211_hw* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_CONNECTION_LOSS_HZ ; 
 int /*<<< orphan*/  ieee80211_beacon_loss (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (struct ieee80211_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_mac_handle_beacon_miss_iter(void *data, u8 *mac,
					       struct ieee80211_vif *vif)
{
	u32 *vdev_id = data;
	struct ath10k_vif *arvif = (void *)vif->drv_priv;
	struct ath10k *ar = arvif->ar;
	struct ieee80211_hw *hw = ar->hw;

	if (arvif->vdev_id != *vdev_id)
		return;

	if (!arvif->is_up)
		return;

	ieee80211_beacon_loss(vif);

	/* Firmware doesn't report beacon loss events repeatedly. If AP probe
	 * (done by mac80211) succeeds but beacons do not resume then it
	 * doesn't make sense to continue operation. Queue connection loss work
	 * which can be cancelled when beacon is received.
	 */
	ieee80211_queue_delayed_work(hw, &arvif->connection_loss_work,
				     ATH10K_CONNECTION_LOSS_HZ);
}