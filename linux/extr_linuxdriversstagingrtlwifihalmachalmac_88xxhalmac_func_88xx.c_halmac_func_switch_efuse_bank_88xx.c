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
typedef  int u8 ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_api; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_efuse_bank { ____Placeholder_halmac_efuse_bank } halmac_efuse_bank ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  HALMAC_EFUSE_CMD_CONSTRUCT_BUSY ; 
 int HALMAC_REG_READ_8 (struct halmac_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,scalar_t__,int) ; 
 int HALMAC_RET_ERROR_STATE ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 int HALMAC_RET_SWITCH_EFUSE_BANK_FAIL ; 
 scalar_t__ REG_LDO_EFUSE_CTRL ; 
 scalar_t__ halmac_transition_efuse_state_88xx (struct halmac_adapter*,int /*<<< orphan*/ ) ; 

enum halmac_ret_status
halmac_func_switch_efuse_bank_88xx(struct halmac_adapter *halmac_adapter,
				   enum halmac_efuse_bank efuse_bank)
{
	u8 reg_value;
	struct halmac_api *halmac_api;

	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	if (halmac_transition_efuse_state_88xx(
		    halmac_adapter, HALMAC_EFUSE_CMD_CONSTRUCT_BUSY) !=
	    HALMAC_RET_SUCCESS)
		return HALMAC_RET_ERROR_STATE;

	reg_value = HALMAC_REG_READ_8(halmac_adapter, REG_LDO_EFUSE_CTRL + 1);

	if (efuse_bank == (reg_value & (BIT(0) | BIT(1))))
		return HALMAC_RET_SUCCESS;

	reg_value &= ~(BIT(0) | BIT(1));
	reg_value |= efuse_bank;
	HALMAC_REG_WRITE_8(halmac_adapter, REG_LDO_EFUSE_CTRL + 1, reg_value);

	if ((HALMAC_REG_READ_8(halmac_adapter, REG_LDO_EFUSE_CTRL + 1) &
	     (BIT(0) | BIT(1))) != efuse_bank)
		return HALMAC_RET_SWITCH_EFUSE_BANK_FAIL;

	return HALMAC_RET_SUCCESS;
}