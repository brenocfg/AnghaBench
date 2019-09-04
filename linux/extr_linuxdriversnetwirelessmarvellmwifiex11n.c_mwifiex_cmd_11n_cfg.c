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
typedef  scalar_t__ u16 ;
struct mwifiex_private {TYPE_1__* adapter; } ;
struct mwifiex_ds_11n_tx_cfg {scalar_t__ misc_config; scalar_t__ tx_htinfo; scalar_t__ tx_htcap; } ;
struct host_cmd_ds_11n_cfg {void* misc_config; void* ht_tx_info; void* ht_tx_cap; void* action; } ;
struct TYPE_4__ {struct host_cmd_ds_11n_cfg htcfg; } ;
struct host_cmd_ds_command {void* size; void* command; TYPE_2__ params; } ;
struct TYPE_3__ {scalar_t__ is_hw_11ac_capable; } ;

/* Variables and functions */
 scalar_t__ HostCmd_CMD_11N_CFG ; 
 scalar_t__ S_DS_GEN ; 
 void* cpu_to_le16 (scalar_t__) ; 

int mwifiex_cmd_11n_cfg(struct mwifiex_private *priv,
			struct host_cmd_ds_command *cmd, u16 cmd_action,
			struct mwifiex_ds_11n_tx_cfg *txcfg)
{
	struct host_cmd_ds_11n_cfg *htcfg = &cmd->params.htcfg;

	cmd->command = cpu_to_le16(HostCmd_CMD_11N_CFG);
	cmd->size = cpu_to_le16(sizeof(struct host_cmd_ds_11n_cfg) + S_DS_GEN);
	htcfg->action = cpu_to_le16(cmd_action);
	htcfg->ht_tx_cap = cpu_to_le16(txcfg->tx_htcap);
	htcfg->ht_tx_info = cpu_to_le16(txcfg->tx_htinfo);

	if (priv->adapter->is_hw_11ac_capable)
		htcfg->misc_config = cpu_to_le16(txcfg->misc_config);

	return 0;
}