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
struct halmac_platform_api {int (* REG_READ_8 ) (void*,scalar_t__) ;} ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_interface; int chip_version; scalar_t__ chip_id; scalar_t__ halmac_api; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_interface { ____Placeholder_halmac_interface } halmac_interface ;
typedef  enum halmac_chip_ver { ____Placeholder_halmac_chip_ver } halmac_chip_ver ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 scalar_t__ HALMAC_CHIP_ID_8197F ; 
 scalar_t__ HALMAC_CHIP_ID_8814B ; 
 scalar_t__ HALMAC_CHIP_ID_8821C ; 
 scalar_t__ HALMAC_CHIP_ID_8822B ; 
 int HALMAC_CHIP_ID_HW_DEF_8197F ; 
 int HALMAC_CHIP_ID_HW_DEF_8814B ; 
 int HALMAC_CHIP_ID_HW_DEF_8821C ; 
 int HALMAC_CHIP_ID_HW_DEF_8822B ; 
 scalar_t__ HALMAC_CHIP_ID_UNDEFINE ; 
 scalar_t__ HALMAC_INTERFACE_SDIO ; 
 int /*<<< orphan*/  HALMAC_MSG_INIT ; 
 int HALMAC_RET_CHIP_NOT_SUPPORT ; 
 int HALMAC_RET_SDIO_LEAVE_SUSPEND_FAIL ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ REG_SDIO_HSUS_CTRL ; 
 scalar_t__ REG_SYS_CFG1 ; 
 scalar_t__ REG_SYS_CFG2 ; 
 int platform_reg_read_8_sdio (void*,struct halmac_platform_api*,scalar_t__) ; 
 int /*<<< orphan*/  platform_reg_write_8_sdio (void*,struct halmac_platform_api*,scalar_t__,int) ; 
 int stub1 (void*,scalar_t__) ; 
 int stub2 (void*,scalar_t__) ; 

__attribute__((used)) static enum halmac_ret_status
halmac_get_chip_info(void *driver_adapter,
		     struct halmac_platform_api *halmac_platform_api,
		     enum halmac_interface halmac_interface,
		     struct halmac_adapter *halmac_adapter)
{
	struct halmac_api *halmac_api = (struct halmac_api *)NULL;
	u8 chip_id, chip_version;
	u32 polling_count;

	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	/* Get Chip_id and Chip_version */
	if (halmac_adapter->halmac_interface == HALMAC_INTERFACE_SDIO) {
		platform_reg_write_8_sdio(
			driver_adapter, halmac_platform_api, REG_SDIO_HSUS_CTRL,
			platform_reg_read_8_sdio(driver_adapter,
						 halmac_platform_api,
						 REG_SDIO_HSUS_CTRL) &
				~(BIT(0)));

		polling_count = 10000;
		while (!(platform_reg_read_8_sdio(driver_adapter,
						  halmac_platform_api,
						  REG_SDIO_HSUS_CTRL) &
			 0x02)) {
			polling_count--;
			if (polling_count == 0)
				return HALMAC_RET_SDIO_LEAVE_SUSPEND_FAIL;
		}

		chip_id = platform_reg_read_8_sdio(
			driver_adapter, halmac_platform_api, REG_SYS_CFG2);
		chip_version = platform_reg_read_8_sdio(driver_adapter,
							halmac_platform_api,
							REG_SYS_CFG1 + 1) >>
			       4;
	} else {
		chip_id = halmac_platform_api->REG_READ_8(driver_adapter,
							  REG_SYS_CFG2);
		chip_version = halmac_platform_api->REG_READ_8(
				       driver_adapter, REG_SYS_CFG1 + 1) >>
			       4;
	}

	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT, DBG_DMESG,
			"[TRACE]Chip id : 0x%X\n", chip_id);
	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT, DBG_DMESG,
			"[TRACE]Chip version : 0x%X\n", chip_version);

	halmac_adapter->chip_version = (enum halmac_chip_ver)chip_version;

	if (chip_id == HALMAC_CHIP_ID_HW_DEF_8822B)
		halmac_adapter->chip_id = HALMAC_CHIP_ID_8822B;
	else if (chip_id == HALMAC_CHIP_ID_HW_DEF_8821C)
		halmac_adapter->chip_id = HALMAC_CHIP_ID_8821C;
	else if (chip_id == HALMAC_CHIP_ID_HW_DEF_8814B)
		halmac_adapter->chip_id = HALMAC_CHIP_ID_8814B;
	else if (chip_id == HALMAC_CHIP_ID_HW_DEF_8197F)
		halmac_adapter->chip_id = HALMAC_CHIP_ID_8197F;
	else
		halmac_adapter->chip_id = HALMAC_CHIP_ID_UNDEFINE;

	if (halmac_adapter->chip_id == HALMAC_CHIP_ID_UNDEFINE)
		return HALMAC_RET_CHIP_NOT_SUPPORT;

	return HALMAC_RET_SUCCESS;
}