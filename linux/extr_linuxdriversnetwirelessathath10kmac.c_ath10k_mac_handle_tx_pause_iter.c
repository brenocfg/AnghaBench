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
struct ath10k_vif {scalar_t__ vdev_id; } ;
struct ath10k_mac_tx_pause {scalar_t__ vdev_id; int /*<<< orphan*/  action; int /*<<< orphan*/  pause_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_mac_vif_handle_tx_pause (struct ath10k_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_mac_handle_tx_pause_iter(void *data, u8 *mac,
					    struct ieee80211_vif *vif)
{
	struct ath10k_vif *arvif = (void *)vif->drv_priv;
	struct ath10k_mac_tx_pause *arg = data;

	if (arvif->vdev_id != arg->vdev_id)
		return;

	ath10k_mac_vif_handle_tx_pause(arvif, arg->pause_id, arg->action);
}