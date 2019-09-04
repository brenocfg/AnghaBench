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
typedef  unsigned int u32 ;
struct TYPE_2__ {void* bcn_len; void* bcn_addr; void* mode; void* vif_id; } ;
struct carl9170_cmd {TYPE_1__ bcn_ctrl; } ;
struct carl9170_bcn_ctrl_cmd {int dummy; } ;
struct ar9170 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_CMD_BCN_CTRL_ASYNC ; 
 int ENOMEM ; 
 int __carl9170_exec_cmd (struct ar9170*,struct carl9170_cmd*,int) ; 
 struct carl9170_cmd* carl9170_cmd_buf (struct ar9170*,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_le32 (unsigned int const) ; 

int carl9170_bcn_ctrl(struct ar9170 *ar, const unsigned int vif_id,
		       const u32 mode, const u32 addr, const u32 len)
{
	struct carl9170_cmd *cmd;

	cmd = carl9170_cmd_buf(ar, CARL9170_CMD_BCN_CTRL_ASYNC,
			       sizeof(struct carl9170_bcn_ctrl_cmd));
	if (!cmd)
		return -ENOMEM;

	cmd->bcn_ctrl.vif_id = cpu_to_le32(vif_id);
	cmd->bcn_ctrl.mode = cpu_to_le32(mode);
	cmd->bcn_ctrl.bcn_addr = cpu_to_le32(addr);
	cmd->bcn_ctrl.bcn_len = cpu_to_le32(len);

	return __carl9170_exec_cmd(ar, cmd, true);
}