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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct lbs_private {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mac; scalar_t__ bbp_rf; } ;
struct TYPE_3__ {void* size; } ;
struct cmd_ds_reg_access {TYPE_2__ value; void* offset; void* action; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 scalar_t__ CMD_ACT_SET ; 
 scalar_t__ CMD_BBP_REG_ACCESS ; 
 scalar_t__ CMD_MAC_REG_ACCESS ; 
 scalar_t__ CMD_RF_REG_ACCESS ; 
 int EINVAL ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,scalar_t__,struct cmd_ds_reg_access*) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_reg_access*,int /*<<< orphan*/ ,int) ; 

int lbs_set_reg(struct lbs_private *priv, u16 reg, u16 offset, u32 value)
{
	struct cmd_ds_reg_access cmd;
	int ret = 0;

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	cmd.offset = cpu_to_le16(offset);

	if (reg == CMD_BBP_REG_ACCESS || reg == CMD_RF_REG_ACCESS)
		cmd.value.bbp_rf = (u8) (value & 0xFF);
	else if (reg == CMD_MAC_REG_ACCESS)
		cmd.value.mac = cpu_to_le32(value);
	else {
		ret = -EINVAL;
		goto out;
	}

	ret = lbs_cmd_with_response(priv, reg, &cmd);

out:
	return ret;
}