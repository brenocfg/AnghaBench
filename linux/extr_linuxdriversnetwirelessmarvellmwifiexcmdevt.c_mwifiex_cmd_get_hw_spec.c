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
struct mwifiex_private {int /*<<< orphan*/  curr_addr; } ;
struct host_cmd_ds_get_hw_spec {int /*<<< orphan*/  permanent_addr; } ;
struct TYPE_2__ {struct host_cmd_ds_get_hw_spec hw_spec; } ;
struct host_cmd_ds_command {void* size; void* command; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ HostCmd_CMD_GET_HW_SPEC ; 
 scalar_t__ S_DS_GEN ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mwifiex_cmd_get_hw_spec(struct mwifiex_private *priv,
			    struct host_cmd_ds_command *cmd)
{
	struct host_cmd_ds_get_hw_spec *hw_spec = &cmd->params.hw_spec;

	cmd->command = cpu_to_le16(HostCmd_CMD_GET_HW_SPEC);
	cmd->size =
		cpu_to_le16(sizeof(struct host_cmd_ds_get_hw_spec) + S_DS_GEN);
	memcpy(hw_spec->permanent_addr, priv->curr_addr, ETH_ALEN);

	return 0;
}