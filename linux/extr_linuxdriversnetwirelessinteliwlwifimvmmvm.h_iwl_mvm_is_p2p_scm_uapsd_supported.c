#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iwl_mvm {TYPE_1__* fw; } ;
struct TYPE_4__ {int uapsd_disable; } ;
struct TYPE_3__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int IWL_DISABLE_UAPSD_P2P_CLIENT ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_P2P_SCM_UAPSD ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ iwlwifi_mod_params ; 

__attribute__((used)) static inline
bool iwl_mvm_is_p2p_scm_uapsd_supported(struct iwl_mvm *mvm)
{
	return fw_has_capa(&mvm->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_P2P_SCM_UAPSD) &&
		!(iwlwifi_mod_params.uapsd_disable &
		  IWL_DISABLE_UAPSD_P2P_CLIENT);
}