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
struct iwl_mvm {int /*<<< orphan*/  trans; TYPE_1__* fw; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_LED_REG ; 
 int /*<<< orphan*/  CSR_LED_REG_TURN_OFF ; 
 int /*<<< orphan*/  CSR_LED_REG_TURN_ON ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_LED_CMD_SUPPORT ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_send_led_fw_cmd (struct iwl_mvm*,int) ; 
 int /*<<< orphan*/  iwl_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_led_set(struct iwl_mvm *mvm, bool on)
{
	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_LED_CMD_SUPPORT)) {
		iwl_mvm_send_led_fw_cmd(mvm, on);
		return;
	}

	iwl_write32(mvm->trans, CSR_LED_REG,
		    on ? CSR_LED_REG_TURN_ON : CSR_LED_REG_TURN_OFF);
}