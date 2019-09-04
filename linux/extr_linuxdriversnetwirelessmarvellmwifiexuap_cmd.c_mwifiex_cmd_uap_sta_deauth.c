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
typedef  int /*<<< orphan*/  u8 ;
struct mwifiex_private {int dummy; } ;
struct host_cmd_ds_sta_deauth {void* reason; int /*<<< orphan*/  mac; } ;
struct TYPE_2__ {struct host_cmd_ds_sta_deauth sta_deauth; } ;
struct host_cmd_ds_command {void* size; void* command; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ HostCmd_CMD_UAP_STA_DEAUTH ; 
 scalar_t__ S_DS_GEN ; 
 scalar_t__ WLAN_REASON_DEAUTH_LEAVING ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_cmd_uap_sta_deauth(struct mwifiex_private *priv,
				      struct host_cmd_ds_command *cmd, u8 *mac)
{
	struct host_cmd_ds_sta_deauth *sta_deauth = &cmd->params.sta_deauth;

	cmd->command = cpu_to_le16(HostCmd_CMD_UAP_STA_DEAUTH);
	memcpy(sta_deauth->mac, mac, ETH_ALEN);
	sta_deauth->reason = cpu_to_le16(WLAN_REASON_DEAUTH_LEAVING);

	cmd->size = cpu_to_le16(sizeof(struct host_cmd_ds_sta_deauth) +
				S_DS_GEN);
	return 0;
}