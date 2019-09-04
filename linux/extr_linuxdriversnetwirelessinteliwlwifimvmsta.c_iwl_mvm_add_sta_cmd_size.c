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
struct iwl_mvm_add_sta_cmd_v7 {int dummy; } ;
struct iwl_mvm_add_sta_cmd {int dummy; } ;
struct iwl_mvm {TYPE_1__* fw; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_UCODE_TLV_API_STA_TYPE ; 
 scalar_t__ fw_has_api (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_has_new_rx_api (struct iwl_mvm*) ; 

__attribute__((used)) static inline int iwl_mvm_add_sta_cmd_size(struct iwl_mvm *mvm)
{
	if (iwl_mvm_has_new_rx_api(mvm) ||
	    fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_STA_TYPE))
		return sizeof(struct iwl_mvm_add_sta_cmd);
	else
		return sizeof(struct iwl_mvm_add_sta_cmd_v7);
}