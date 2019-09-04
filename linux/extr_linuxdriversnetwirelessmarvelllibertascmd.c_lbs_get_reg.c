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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct lbs_private {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mac; int /*<<< orphan*/  bbp_rf; } ;
struct TYPE_3__ {void* size; } ;
struct cmd_ds_reg_access {TYPE_2__ value; void* offset; void* action; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ CMD_ACT_GET ; 
 scalar_t__ CMD_BBP_REG_ACCESS ; 
 scalar_t__ CMD_MAC_REG_ACCESS ; 
 scalar_t__ CMD_RF_REG_ACCESS ; 
 int EINVAL ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int lbs_cmd_with_response (struct lbs_private*,scalar_t__,struct cmd_ds_reg_access*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_reg_access*,int /*<<< orphan*/ ,int) ; 

int lbs_get_reg(struct lbs_private *priv, u16 reg, u16 offset, u32 *value)
{
	struct cmd_ds_reg_access cmd;
	int ret = 0;

	BUG_ON(value == NULL);

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_GET);
	cmd.offset = cpu_to_le16(offset);

	if (reg != CMD_MAC_REG_ACCESS &&
	    reg != CMD_BBP_REG_ACCESS &&
	    reg != CMD_RF_REG_ACCESS) {
		ret = -EINVAL;
		goto out;
	}

	ret = lbs_cmd_with_response(priv, reg, &cmd);
	if (!ret) {
		if (reg == CMD_BBP_REG_ACCESS || reg == CMD_RF_REG_ACCESS)
			*value = cmd.value.bbp_rf;
		else if (reg == CMD_MAC_REG_ACCESS)
			*value = le32_to_cpu(cmd.value.mac);
	}

out:
	return ret;
}