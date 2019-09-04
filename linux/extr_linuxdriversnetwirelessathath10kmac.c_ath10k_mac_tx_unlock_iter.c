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
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ath10k_vif {int /*<<< orphan*/  vdev_id; scalar_t__ tx_paused; } ;
struct ath10k {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_wake_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_mac_tx_unlock_iter(void *data, u8 *mac,
				      struct ieee80211_vif *vif)
{
	struct ath10k *ar = data;
	struct ath10k_vif *arvif = (void *)vif->drv_priv;

	if (arvif->tx_paused)
		return;

	ieee80211_wake_queue(ar->hw, arvif->vdev_id);
}