#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct mwifiex_private {int dummy; } ;
struct mwifiex_ds_reg_rw {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HostCmd_CMD_BBP_REG_ACCESS ; 
 int /*<<< orphan*/  HostCmd_CMD_CAU_REG_ACCESS ; 
 int /*<<< orphan*/  HostCmd_CMD_MAC_REG_ACCESS ; 
 int /*<<< orphan*/  HostCmd_CMD_PMIC_REG_ACCESS ; 
 int /*<<< orphan*/  HostCmd_CMD_RF_REG_ACCESS ; 
#define  MWIFIEX_REG_BBP 132 
#define  MWIFIEX_REG_CAU 131 
#define  MWIFIEX_REG_MAC 130 
#define  MWIFIEX_REG_PMIC 129 
#define  MWIFIEX_REG_RF 128 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mwifiex_ds_reg_rw*,int) ; 

__attribute__((used)) static int mwifiex_reg_mem_ioctl_reg_rw(struct mwifiex_private *priv,
					struct mwifiex_ds_reg_rw *reg_rw,
					u16 action)
{
	u16 cmd_no;

	switch (reg_rw->type) {
	case MWIFIEX_REG_MAC:
		cmd_no = HostCmd_CMD_MAC_REG_ACCESS;
		break;
	case MWIFIEX_REG_BBP:
		cmd_no = HostCmd_CMD_BBP_REG_ACCESS;
		break;
	case MWIFIEX_REG_RF:
		cmd_no = HostCmd_CMD_RF_REG_ACCESS;
		break;
	case MWIFIEX_REG_PMIC:
		cmd_no = HostCmd_CMD_PMIC_REG_ACCESS;
		break;
	case MWIFIEX_REG_CAU:
		cmd_no = HostCmd_CMD_CAU_REG_ACCESS;
		break;
	default:
		return -1;
	}

	return mwifiex_send_cmd(priv, cmd_no, action, 0, reg_rw, true);
}