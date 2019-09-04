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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct mwifiex_private {int dummy; } ;
struct TYPE_4__ {void* len; void* type; } ;
struct mwifiex_ie_types_robust_coex {void* mode; TYPE_2__ header; } ;
struct host_cmd_ds_robust_coex {scalar_t__ action; } ;
struct TYPE_3__ {struct host_cmd_ds_robust_coex coex; } ;
struct host_cmd_ds_command {void* size; void* command; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ HostCmd_ACT_GEN_GET ; 
 int HostCmd_CMD_ROBUST_COEX ; 
 int /*<<< orphan*/  MWIFIEX_COEX_MODE_SPATIAL ; 
 int /*<<< orphan*/  MWIFIEX_COEX_MODE_TIMESHARE ; 
 int S_DS_GEN ; 
 int TLV_TYPE_ROBUST_COEX ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_cmd_robust_coex(struct mwifiex_private *priv,
				   struct host_cmd_ds_command *cmd,
				   u16 cmd_action, bool *is_timeshare)
{
	struct host_cmd_ds_robust_coex *coex = &cmd->params.coex;
	struct mwifiex_ie_types_robust_coex *coex_tlv;

	cmd->command = cpu_to_le16(HostCmd_CMD_ROBUST_COEX);
	cmd->size = cpu_to_le16(sizeof(*coex) + sizeof(*coex_tlv) + S_DS_GEN);

	coex->action = cpu_to_le16(cmd_action);
	coex_tlv = (struct mwifiex_ie_types_robust_coex *)
				((u8 *)coex + sizeof(*coex));
	coex_tlv->header.type = cpu_to_le16(TLV_TYPE_ROBUST_COEX);
	coex_tlv->header.len = cpu_to_le16(sizeof(coex_tlv->mode));

	if (coex->action == HostCmd_ACT_GEN_GET)
		return 0;

	if (*is_timeshare)
		coex_tlv->mode = cpu_to_le32(MWIFIEX_COEX_MODE_TIMESHARE);
	else
		coex_tlv->mode = cpu_to_le32(MWIFIEX_COEX_MODE_SPATIAL);

	return 0;
}