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
struct iwl_mvm_tof_data {int /*<<< orphan*/  active_range_request; } ;
struct iwl_mvm {int init_status; struct iwl_mvm_tof_data tof_data; TYPE_1__* fw; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int IWL_MVM_INIT_STATUS_TOF_INIT_COMPLETE ; 
 int /*<<< orphan*/  IWL_MVM_TOF_RANGE_REQ_MAX_ID ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_TOF_SUPPORT ; 
 int /*<<< orphan*/  fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iwl_mvm_tof_data*,int /*<<< orphan*/ ,int) ; 

void iwl_mvm_tof_clean(struct iwl_mvm *mvm)
{
	struct iwl_mvm_tof_data *tof_data = &mvm->tof_data;

	if (!fw_has_capa(&mvm->fw->ucode_capa,
			 IWL_UCODE_TLV_CAPA_TOF_SUPPORT) ||
	    !(mvm->init_status & IWL_MVM_INIT_STATUS_TOF_INIT_COMPLETE))
		return;

	memset(tof_data, 0, sizeof(*tof_data));
	mvm->tof_data.active_range_request = IWL_MVM_TOF_RANGE_REQ_MAX_ID;
	mvm->init_status &= ~IWL_MVM_INIT_STATUS_TOF_INIT_COMPLETE;
}