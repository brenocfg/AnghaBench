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
struct mwifiex_private {scalar_t__ bcn_nf_avg; scalar_t__ bcn_rssi_avg; scalar_t__ bcn_nf_last; scalar_t__ bcn_rssi_last; scalar_t__ data_nf_avg; scalar_t__ data_rssi_avg; scalar_t__ data_nf_last; scalar_t__ data_rssi_last; scalar_t__ bcn_avg_factor; scalar_t__ data_avg_factor; } ;
struct TYPE_3__ {void* nbcn; void* ndata; void* action; } ;
struct TYPE_4__ {TYPE_1__ rssi_info; } ;
struct host_cmd_ds_command {TYPE_2__ params; void* size; void* command; } ;
struct host_cmd_ds_802_11_rssi_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ HostCmd_CMD_RSSI_INFO ; 
 scalar_t__ S_DS_GEN ; 
 void* cpu_to_le16 (scalar_t__) ; 

__attribute__((used)) static int
mwifiex_cmd_802_11_rssi_info(struct mwifiex_private *priv,
			     struct host_cmd_ds_command *cmd, u16 cmd_action)
{
	cmd->command = cpu_to_le16(HostCmd_CMD_RSSI_INFO);
	cmd->size = cpu_to_le16(sizeof(struct host_cmd_ds_802_11_rssi_info) +
				S_DS_GEN);
	cmd->params.rssi_info.action = cpu_to_le16(cmd_action);
	cmd->params.rssi_info.ndata = cpu_to_le16(priv->data_avg_factor);
	cmd->params.rssi_info.nbcn = cpu_to_le16(priv->bcn_avg_factor);

	/* Reset SNR/NF/RSSI values in private structure */
	priv->data_rssi_last = 0;
	priv->data_nf_last = 0;
	priv->data_rssi_avg = 0;
	priv->data_nf_avg = 0;
	priv->bcn_rssi_last = 0;
	priv->bcn_nf_last = 0;
	priv->bcn_rssi_avg = 0;
	priv->bcn_nf_avg = 0;

	return 0;
}