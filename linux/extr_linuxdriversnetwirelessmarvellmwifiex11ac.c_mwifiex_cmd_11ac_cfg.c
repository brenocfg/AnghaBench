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
typedef  scalar_t__ u16 ;
struct mwifiex_private {int dummy; } ;
struct mwifiex_11ac_vht_cfg {int /*<<< orphan*/  mcs_rx_set; int /*<<< orphan*/  mcs_tx_set; int /*<<< orphan*/  cap_info; int /*<<< orphan*/  misc_config; int /*<<< orphan*/  band_config; } ;
struct host_cmd_11ac_vht_cfg {void* mcs_rx_set; void* mcs_tx_set; void* cap_info; int /*<<< orphan*/  misc_config; int /*<<< orphan*/  band_config; void* action; } ;
struct TYPE_2__ {struct host_cmd_11ac_vht_cfg vht_cfg; } ;
struct host_cmd_ds_command {void* size; void* command; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ HostCmd_CMD_11AC_CFG ; 
 scalar_t__ S_DS_GEN ; 
 void* cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 

int mwifiex_cmd_11ac_cfg(struct mwifiex_private *priv,
			 struct host_cmd_ds_command *cmd, u16 cmd_action,
			 struct mwifiex_11ac_vht_cfg *cfg)
{
	struct host_cmd_11ac_vht_cfg *vhtcfg = &cmd->params.vht_cfg;

	cmd->command = cpu_to_le16(HostCmd_CMD_11AC_CFG);
	cmd->size = cpu_to_le16(sizeof(struct host_cmd_11ac_vht_cfg) +
				S_DS_GEN);
	vhtcfg->action = cpu_to_le16(cmd_action);
	vhtcfg->band_config = cfg->band_config;
	vhtcfg->misc_config = cfg->misc_config;
	vhtcfg->cap_info = cpu_to_le32(cfg->cap_info);
	vhtcfg->mcs_tx_set = cpu_to_le32(cfg->mcs_tx_set);
	vhtcfg->mcs_rx_set = cpu_to_le32(cfg->mcs_rx_set);

	return 0;
}