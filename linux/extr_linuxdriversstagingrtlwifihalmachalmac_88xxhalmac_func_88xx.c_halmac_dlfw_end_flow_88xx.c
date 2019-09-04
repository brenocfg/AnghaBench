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
typedef  int /*<<< orphan*/  u16 ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_api; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int BIT (int) ; 
 int BIT_FW_DW_RDY ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  HALMAC_MSG_INIT ; 
 int HALMAC_REG_READ_16 (struct halmac_adapter*,scalar_t__) ; 
 int HALMAC_REG_READ_32 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int HALMAC_REG_READ_8 (struct halmac_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_16 (struct halmac_adapter*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_32 (struct halmac_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,scalar_t__,int) ; 
 int HALMAC_RET_DLFW_FAIL ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  REG_FW_DBG7 ; 
 scalar_t__ REG_MCUFW_CTRL ; 
 scalar_t__ REG_RSV_CTRL ; 
 scalar_t__ REG_SYS_FUNC_EN ; 
 int /*<<< orphan*/  REG_TXDMA_STATUS ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

enum halmac_ret_status
halmac_dlfw_end_flow_88xx(struct halmac_adapter *halmac_adapter)
{
	u8 value8;
	u32 counter;
	void *driver_adapter = halmac_adapter->driver_adapter;
	struct halmac_api *halmac_api =
		(struct halmac_api *)halmac_adapter->halmac_api;

	HALMAC_REG_WRITE_32(halmac_adapter, REG_TXDMA_STATUS, BIT(2));

	/* Check IMEM & DMEM checksum is OK or not */
	if ((HALMAC_REG_READ_8(halmac_adapter, REG_MCUFW_CTRL) & 0x50) == 0x50)
		HALMAC_REG_WRITE_16(halmac_adapter, REG_MCUFW_CTRL,
				    (u16)(HALMAC_REG_READ_16(halmac_adapter,
							     REG_MCUFW_CTRL) |
					  BIT_FW_DW_RDY));
	else
		return HALMAC_RET_DLFW_FAIL;

	HALMAC_REG_WRITE_8(
		halmac_adapter, REG_MCUFW_CTRL,
		(u8)(HALMAC_REG_READ_8(halmac_adapter, REG_MCUFW_CTRL) &
		     ~(BIT(0))));

	value8 = HALMAC_REG_READ_8(halmac_adapter, REG_RSV_CTRL + 1);
	value8 = (u8)(value8 | BIT(0));
	HALMAC_REG_WRITE_8(halmac_adapter, REG_RSV_CTRL + 1, value8);

	value8 = HALMAC_REG_READ_8(halmac_adapter, REG_SYS_FUNC_EN + 1);
	value8 = (u8)(value8 | BIT(2));
	HALMAC_REG_WRITE_8(halmac_adapter, REG_SYS_FUNC_EN + 1,
			   value8); /* Release MCU reset */
	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT, DBG_DMESG,
			"Download Finish, Reset CPU\n");

	counter = 10000;
	while (HALMAC_REG_READ_16(halmac_adapter, REG_MCUFW_CTRL) != 0xC078) {
		if (counter == 0) {
			pr_err("Check 0x80 = 0xC078 fail\n");
			if ((HALMAC_REG_READ_32(halmac_adapter, REG_FW_DBG7) &
			     0xFFFFFF00) == 0xFAAAAA00)
				pr_err("Key fail\n");
			return HALMAC_RET_DLFW_FAIL;
		}
		counter--;
		usleep_range(50, 60);
	}

	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT, DBG_DMESG,
			"Check 0x80 = 0xC078 counter = %d\n", counter);

	return HALMAC_RET_SUCCESS;
}