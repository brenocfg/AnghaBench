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
struct ath10k_vif {int /*<<< orphan*/  vdev_id; struct ath10k* ar; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_lock; } ;
struct ath10k {TYPE_1__ htt; } ;
typedef  enum wmi_tlv_tx_pause_id { ____Placeholder_wmi_tlv_tx_pause_id } wmi_tlv_tx_pause_id ;
typedef  enum wmi_tlv_tx_pause_action { ____Placeholder_wmi_tlv_tx_pause_action } wmi_tlv_tx_pause_action ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
#define  WMI_TLV_TX_PAUSE_ACTION_STOP 129 
#define  WMI_TLV_TX_PAUSE_ACTION_WAKE 128 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_mac_vif_tx_lock (struct ath10k_vif*,int) ; 
 int /*<<< orphan*/  ath10k_mac_vif_tx_unlock (struct ath10k_vif*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_mac_vif_handle_tx_pause(struct ath10k_vif *arvif,
					   enum wmi_tlv_tx_pause_id pause_id,
					   enum wmi_tlv_tx_pause_action action)
{
	struct ath10k *ar = arvif->ar;

	lockdep_assert_held(&ar->htt.tx_lock);

	switch (action) {
	case WMI_TLV_TX_PAUSE_ACTION_STOP:
		ath10k_mac_vif_tx_lock(arvif, pause_id);
		break;
	case WMI_TLV_TX_PAUSE_ACTION_WAKE:
		ath10k_mac_vif_tx_unlock(arvif, pause_id);
		break;
	default:
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "received unknown tx pause action %d on vdev %i, ignoring\n",
			    action, arvif->vdev_id);
		break;
	}
}