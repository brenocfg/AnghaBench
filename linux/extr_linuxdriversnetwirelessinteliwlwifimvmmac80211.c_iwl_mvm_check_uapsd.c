#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {int /*<<< orphan*/  rate; } ;
struct iwl_mvm_tcm_mac {int opened_rx_ba_sessions; TYPE_2__ uapsd_nonagg_detect; } ;
struct TYPE_8__ {struct iwl_mvm_tcm_mac* data; } ;
struct iwl_mvm {TYPE_5__* uapsd_noagg_bssids; TYPE_4__* fw; TYPE_1__ tcm; int /*<<< orphan*/  status; } ;
struct ieee80211_vif {int /*<<< orphan*/  driver_flags; scalar_t__ p2p; } ;
struct TYPE_14__ {size_t id; } ;
struct TYPE_13__ {int uapsd_disable; } ;
struct TYPE_12__ {int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {int flags; } ;
struct TYPE_11__ {TYPE_3__ ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_VIF_SUPPORTS_UAPSD ; 
 int IWL_DISABLE_UAPSD_BSS ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 int IWL_MVM_UAPSD_NOAGG_LIST_LEN ; 
 int IWL_UCODE_TLV_FLAGS_UAPSD_SUPPORT ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ewma_rate_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_is_p2p_scm_uapsd_supported (struct iwl_mvm*) ; 
 TYPE_7__* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 TYPE_6__ iwlwifi_mod_params ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_check_uapsd(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
				const u8 *bssid)
{
	int i;

	if (!test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)) {
		struct iwl_mvm_tcm_mac *mdata;

		mdata = &mvm->tcm.data[iwl_mvm_vif_from_mac80211(vif)->id];
		ewma_rate_init(&mdata->uapsd_nonagg_detect.rate);
		mdata->opened_rx_ba_sessions = false;
	}

	if (!(mvm->fw->ucode_capa.flags & IWL_UCODE_TLV_FLAGS_UAPSD_SUPPORT))
		return;

	if (vif->p2p && !iwl_mvm_is_p2p_scm_uapsd_supported(mvm)) {
		vif->driver_flags &= ~IEEE80211_VIF_SUPPORTS_UAPSD;
		return;
	}

	if (!vif->p2p &&
	    (iwlwifi_mod_params.uapsd_disable & IWL_DISABLE_UAPSD_BSS)) {
		vif->driver_flags &= ~IEEE80211_VIF_SUPPORTS_UAPSD;
		return;
	}

	for (i = 0; i < IWL_MVM_UAPSD_NOAGG_LIST_LEN; i++) {
		if (ether_addr_equal(mvm->uapsd_noagg_bssids[i].addr, bssid)) {
			vif->driver_flags &= ~IEEE80211_VIF_SUPPORTS_UAPSD;
			return;
		}
	}

	vif->driver_flags |= IEEE80211_VIF_SUPPORTS_UAPSD;
}