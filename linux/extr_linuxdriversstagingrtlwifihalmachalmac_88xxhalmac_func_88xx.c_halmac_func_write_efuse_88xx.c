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
typedef  int u32 ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {int hal_efuse_map_valid; int /*<<< orphan*/  efuse_lock; scalar_t__ halmac_api; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int BIT (int) ; 
 int BIT_EF_FLAG ; 
 int BIT_MASK_EF_ADDR ; 
 int BIT_MASK_EF_DATA ; 
 int BIT_SHIFT_EF_ADDR ; 
 int HALMAC_REG_READ_32 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int HALMAC_REG_READ_8 (struct halmac_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_32 (struct halmac_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,scalar_t__,int const) ; 
 int HALMAC_RET_EFUSE_W_FAIL ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  REG_EFUSE_CTRL ; 
 scalar_t__ REG_LDO_EFUSE_CTRL ; 
 scalar_t__ REG_PMC_DBG_CTRL2 ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

enum halmac_ret_status
halmac_func_write_efuse_88xx(struct halmac_adapter *halmac_adapter, u32 offset,
			     u8 value)
{
	const u8 wite_protect_code = 0x69;
	u32 value32, tmp32, counter;
	void *driver_adapter = NULL;
	struct halmac_api *halmac_api;

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	spin_lock(&halmac_adapter->efuse_lock);
	halmac_adapter->hal_efuse_map_valid = false;
	spin_unlock(&halmac_adapter->efuse_lock);

	HALMAC_REG_WRITE_8(halmac_adapter, REG_PMC_DBG_CTRL2 + 3,
			   wite_protect_code);

	/* Enable 2.5V LDO */
	HALMAC_REG_WRITE_8(
		halmac_adapter, REG_LDO_EFUSE_CTRL + 3,
		(u8)(HALMAC_REG_READ_8(halmac_adapter, REG_LDO_EFUSE_CTRL + 3) |
		     BIT(7)));

	value32 = HALMAC_REG_READ_32(halmac_adapter, REG_EFUSE_CTRL);
	value32 =
		value32 &
		~((BIT_MASK_EF_DATA) | (BIT_MASK_EF_ADDR << BIT_SHIFT_EF_ADDR));
	value32 = value32 | ((offset & BIT_MASK_EF_ADDR) << BIT_SHIFT_EF_ADDR) |
		  (value & BIT_MASK_EF_DATA);
	HALMAC_REG_WRITE_32(halmac_adapter, REG_EFUSE_CTRL,
			    value32 | BIT_EF_FLAG);

	counter = 1000000;
	do {
		udelay(1);
		tmp32 = HALMAC_REG_READ_32(halmac_adapter, REG_EFUSE_CTRL);
		counter--;
		if (counter == 0) {
			pr_err("halmac_write_efuse Fail !!\n");
			return HALMAC_RET_EFUSE_W_FAIL;
		}
	} while ((tmp32 & BIT_EF_FLAG) == BIT_EF_FLAG);

	HALMAC_REG_WRITE_8(halmac_adapter, REG_PMC_DBG_CTRL2 + 3, 0x00);

	/* Disable 2.5V LDO */
	HALMAC_REG_WRITE_8(
		halmac_adapter, REG_LDO_EFUSE_CTRL + 3,
		(u8)(HALMAC_REG_READ_8(halmac_adapter, REG_LDO_EFUSE_CTRL + 3) &
		     ~(BIT(7))));

	return HALMAC_RET_SUCCESS;
}