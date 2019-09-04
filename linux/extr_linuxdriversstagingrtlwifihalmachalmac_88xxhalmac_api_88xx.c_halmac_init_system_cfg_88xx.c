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
typedef  int /*<<< orphan*/  u32 ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_api; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int BIT_LTE_MUX_CTRL_PATH ; 
 int BIT_WL_PLATFORM_RST ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  HALMAC_API_INIT_SYSTEM_CFG ; 
 int /*<<< orphan*/  HALMAC_FUNCTION_ENABLE_88XX ; 
 int /*<<< orphan*/  HALMAC_MSG_INIT ; 
 int HALMAC_REG_READ_32 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_32 (struct halmac_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,scalar_t__,int /*<<< orphan*/ ) ; 
 int HALMAC_RET_ADAPTER_INVALID ; 
 int HALMAC_RET_API_INVALID ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  REG_CPU_DMEM_CON ; 
 scalar_t__ REG_SYS_FUNC_EN ; 
 int /*<<< orphan*/  REG_SYS_SDIO_CTRL ; 
 scalar_t__ halmac_adapter_validate (struct halmac_adapter*) ; 
 int /*<<< orphan*/  halmac_api_record_id_88xx (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ halmac_api_validate (struct halmac_adapter*) ; 

enum halmac_ret_status
halmac_init_system_cfg_88xx(struct halmac_adapter *halmac_adapter)
{
	void *driver_adapter = NULL;
	struct halmac_api *halmac_api;

	if (halmac_adapter_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_ADAPTER_INVALID;

	if (halmac_api_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_API_INVALID;

	halmac_api_record_id_88xx(halmac_adapter, HALMAC_API_INIT_SYSTEM_CFG);

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT, DBG_DMESG,
			"halmac_init_system_cfg ==========>\n");

	HALMAC_REG_WRITE_8(halmac_adapter, REG_SYS_FUNC_EN + 1,
			   HALMAC_FUNCTION_ENABLE_88XX);
	HALMAC_REG_WRITE_32(
		halmac_adapter, REG_SYS_SDIO_CTRL,
		(u32)(HALMAC_REG_READ_32(halmac_adapter, REG_SYS_SDIO_CTRL) |
		      BIT_LTE_MUX_CTRL_PATH));
	HALMAC_REG_WRITE_32(
		halmac_adapter, REG_CPU_DMEM_CON,
		(u32)(HALMAC_REG_READ_32(halmac_adapter, REG_CPU_DMEM_CON) |
		      BIT_WL_PLATFORM_RST));

	/* halmac_api->halmac_init_h2c(halmac_adapter); */

	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT, DBG_DMESG,
			"halmac_init_system_cfg <==========\n");

	return HALMAC_RET_SUCCESS;
}