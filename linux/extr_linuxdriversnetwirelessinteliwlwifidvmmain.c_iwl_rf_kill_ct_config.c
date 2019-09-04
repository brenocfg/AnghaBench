#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ct_kill_threshold; int /*<<< orphan*/  ct_kill_exit_threshold; } ;
struct TYPE_4__ {int ct_kill_toggle; } ;
struct iwl_priv {TYPE_3__ hw_params; TYPE_2__* lib; TYPE_1__ thermal_throttle; int /*<<< orphan*/  trans; } ;
struct iwl_ct_kill_throttling_config {void* critical_temperature_R; void* critical_temperature_exit; void* critical_temperature_enter; } ;
struct iwl_ct_kill_config {void* critical_temperature_R; void* critical_temperature_exit; void* critical_temperature_enter; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  adv_cmd ;
struct TYPE_5__ {scalar_t__ support_ct_kill_exit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_CLR ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_REG_BIT_CT_KILL_EXIT ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  REPLY_CT_KILL_CONFIG_CMD ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int iwl_dvm_send_cmd_pdu (struct iwl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_ct_kill_throttling_config*) ; 
 int /*<<< orphan*/  iwl_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_rf_kill_ct_config(struct iwl_priv *priv)
{
	struct iwl_ct_kill_config cmd;
	struct iwl_ct_kill_throttling_config adv_cmd;
	int ret = 0;

	iwl_write32(priv->trans, CSR_UCODE_DRV_GP1_CLR,
		    CSR_UCODE_DRV_GP1_REG_BIT_CT_KILL_EXIT);

	priv->thermal_throttle.ct_kill_toggle = false;

	if (priv->lib->support_ct_kill_exit) {
		adv_cmd.critical_temperature_enter =
			cpu_to_le32(priv->hw_params.ct_kill_threshold);
		adv_cmd.critical_temperature_exit =
			cpu_to_le32(priv->hw_params.ct_kill_exit_threshold);

		ret = iwl_dvm_send_cmd_pdu(priv,
				       REPLY_CT_KILL_CONFIG_CMD,
				       0, sizeof(adv_cmd), &adv_cmd);
		if (ret)
			IWL_ERR(priv, "REPLY_CT_KILL_CONFIG_CMD failed\n");
		else
			IWL_DEBUG_INFO(priv, "REPLY_CT_KILL_CONFIG_CMD "
				"succeeded, critical temperature enter is %d,"
				"exit is %d\n",
				priv->hw_params.ct_kill_threshold,
				priv->hw_params.ct_kill_exit_threshold);
	} else {
		cmd.critical_temperature_R =
			cpu_to_le32(priv->hw_params.ct_kill_threshold);

		ret = iwl_dvm_send_cmd_pdu(priv,
				       REPLY_CT_KILL_CONFIG_CMD,
				       0, sizeof(cmd), &cmd);
		if (ret)
			IWL_ERR(priv, "REPLY_CT_KILL_CONFIG_CMD failed\n");
		else
			IWL_DEBUG_INFO(priv, "REPLY_CT_KILL_CONFIG_CMD "
				"succeeded, "
				"critical temperature is %d\n",
				priv->hw_params.ct_kill_threshold);
	}
}