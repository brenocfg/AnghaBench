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
typedef  int u32 ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_interface; scalar_t__ halmac_api; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  HALMAC_API_PRE_INIT_SYSTEM_CFG ; 
 int /*<<< orphan*/  HALMAC_HW_EN_BB_RF ; 
 scalar_t__ HALMAC_INTERFACE_SDIO ; 
 scalar_t__ HALMAC_INTERFACE_USB ; 
 int /*<<< orphan*/  HALMAC_MSG_INIT ; 
 int HALMAC_REG_READ_32 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int HALMAC_REG_READ_8 (struct halmac_adapter*,int) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_32 (struct halmac_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,int,int) ; 
 int HALMAC_RET_ADAPTER_INVALID ; 
 int HALMAC_RET_API_INVALID ; 
 int HALMAC_RET_SDIO_LEAVE_SUSPEND_FAIL ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  REG_GPIO_MUXCFG ; 
 int /*<<< orphan*/  REG_LED_CFG ; 
 int /*<<< orphan*/  REG_PAD_CTRL1 ; 
 int REG_SDIO_HSUS_CTRL ; 
 int REG_SYS_CFG2 ; 
 scalar_t__ halmac_adapter_validate (struct halmac_adapter*) ; 
 int /*<<< orphan*/  halmac_api_record_id_88xx (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ halmac_api_validate (struct halmac_adapter*) ; 
 int /*<<< orphan*/  halmac_set_hw_value_88xx (struct halmac_adapter*,int /*<<< orphan*/ ,int*) ; 

enum halmac_ret_status
halmac_pre_init_system_cfg_88xx(struct halmac_adapter *halmac_adapter)
{
	u32 value32, counter;
	void *driver_adapter = NULL;
	struct halmac_api *halmac_api;
	bool enable_bb;

	if (halmac_adapter_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_ADAPTER_INVALID;

	if (halmac_api_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_API_INVALID;

	halmac_api_record_id_88xx(halmac_adapter,
				  HALMAC_API_PRE_INIT_SYSTEM_CFG);

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT, DBG_DMESG,
			"halmac_pre_init_system_cfg ==========>\n");

	if (halmac_adapter->halmac_interface == HALMAC_INTERFACE_SDIO) {
		HALMAC_REG_WRITE_8(
			halmac_adapter, REG_SDIO_HSUS_CTRL,
			HALMAC_REG_READ_8(halmac_adapter, REG_SDIO_HSUS_CTRL) &
				~(BIT(0)));
		counter = 10000;
		while (!(HALMAC_REG_READ_8(halmac_adapter, REG_SDIO_HSUS_CTRL) &
			 0x02)) {
			counter--;
			if (counter == 0)
				return HALMAC_RET_SDIO_LEAVE_SUSPEND_FAIL;
		}
	} else if (halmac_adapter->halmac_interface == HALMAC_INTERFACE_USB) {
		if (HALMAC_REG_READ_8(halmac_adapter, REG_SYS_CFG2 + 3) ==
		    0x20) /* usb3.0 */
			HALMAC_REG_WRITE_8(
				halmac_adapter, 0xFE5B,
				HALMAC_REG_READ_8(halmac_adapter, 0xFE5B) |
					BIT(4));
	}

	/* Config PIN Mux */
	value32 = HALMAC_REG_READ_32(halmac_adapter, REG_PAD_CTRL1);
	value32 = value32 & (~(BIT(28) | BIT(29)));
	value32 = value32 | BIT(28) | BIT(29);
	HALMAC_REG_WRITE_32(halmac_adapter, REG_PAD_CTRL1, value32);

	value32 = HALMAC_REG_READ_32(halmac_adapter, REG_LED_CFG);
	value32 = value32 & (~(BIT(25) | BIT(26)));
	HALMAC_REG_WRITE_32(halmac_adapter, REG_LED_CFG, value32);

	value32 = HALMAC_REG_READ_32(halmac_adapter, REG_GPIO_MUXCFG);
	value32 = value32 & (~(BIT(2)));
	value32 = value32 | BIT(2);
	HALMAC_REG_WRITE_32(halmac_adapter, REG_GPIO_MUXCFG, value32);

	enable_bb = false;
	halmac_set_hw_value_88xx(halmac_adapter, HALMAC_HW_EN_BB_RF,
				 &enable_bb);

	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT, DBG_DMESG,
			"halmac_pre_init_system_cfg <==========\n");

	return HALMAC_RET_SUCCESS;
}