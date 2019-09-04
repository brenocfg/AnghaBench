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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct halmac_api {int dummy; } ;
struct TYPE_2__ {int mac_power; int /*<<< orphan*/  ps_state; int /*<<< orphan*/  dlfw_state; } ;
struct halmac_adapter {int rpwm_record; TYPE_1__ halmac_state; scalar_t__ halmac_api; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_mac_power { ____Placeholder_halmac_mac_power } halmac_mac_power ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 int /*<<< orphan*/  HALMAC_8822B_PWR_SEQ_VER ; 
 int /*<<< orphan*/  HALMAC_DLFW_NONE ; 
 int HALMAC_MAC_POWER_OFF ; 
 int HALMAC_MAC_POWER_ON ; 
 int /*<<< orphan*/  HALMAC_MSG_PWR ; 
 int /*<<< orphan*/  HALMAC_PS_STATE_ACT ; 
 int /*<<< orphan*/  HALMAC_PS_STATE_UNDEFINE ; 
 int /*<<< orphan*/  HALMAC_PWR_CUT_ALL_MSK ; 
 int /*<<< orphan*/  HALMAC_PWR_FAB_TSMC_MSK ; 
 int HALMAC_PWR_INTF_SDIO_MSK ; 
 int HALMAC_REG_READ_16 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HALMAC_REG_READ_32 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 void* HALMAC_REG_READ_8 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_32 (struct halmac_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,int /*<<< orphan*/ ,int) ; 
 int HALMAC_RET_ADAPTER_INVALID ; 
 int HALMAC_RET_API_INVALID ; 
 int HALMAC_RET_POWER_OFF_FAIL ; 
 int HALMAC_RET_POWER_ON_FAIL ; 
 int HALMAC_RET_PWR_UNCHANGE ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  REG_CR ; 
 int /*<<< orphan*/  REG_MCUFW_CTRL ; 
 int /*<<< orphan*/  REG_SDIO_HIMR ; 
 int /*<<< orphan*/  REG_SDIO_HRPWM1 ; 
 int /*<<< orphan*/  halmac_8822b_card_disable_flow ; 
 int /*<<< orphan*/  halmac_8822b_card_enable_flow ; 
 scalar_t__ halmac_adapter_validate (struct halmac_adapter*) ; 
 scalar_t__ halmac_api_validate (struct halmac_adapter*) ; 
 int /*<<< orphan*/  halmac_init_adapter_dynamic_para_88xx (struct halmac_adapter*) ; 
 scalar_t__ halmac_pwr_seq_parser_88xx (struct halmac_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

enum halmac_ret_status
halmac_mac_power_switch_8822b_sdio(struct halmac_adapter *halmac_adapter,
				   enum halmac_mac_power halmac_power)
{
	u8 interface_mask;
	u8 value8;
	u8 rpwm;
	u32 imr_backup;
	void *driver_adapter = NULL;
	struct halmac_api *halmac_api;

	if (halmac_adapter_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_ADAPTER_INVALID;

	if (halmac_api_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_API_INVALID;

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	HALMAC_RT_TRACE(
		driver_adapter, HALMAC_MSG_PWR, DBG_DMESG,
		"[TRACE]halmac_mac_power_switch_88xx_sdio==========>\n");
	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_PWR, DBG_DMESG,
			"[TRACE]halmac_power = %x ==========>\n", halmac_power);
	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_PWR, DBG_DMESG,
			"[TRACE]8822B pwr seq ver = %s\n",
			HALMAC_8822B_PWR_SEQ_VER);

	interface_mask = HALMAC_PWR_INTF_SDIO_MSK;

	halmac_adapter->rpwm_record =
		HALMAC_REG_READ_8(halmac_adapter, REG_SDIO_HRPWM1);

	/* Check FW still exist or not */
	if (HALMAC_REG_READ_16(halmac_adapter, REG_MCUFW_CTRL) == 0xC078) {
		/* Leave 32K */
		rpwm = (u8)((halmac_adapter->rpwm_record ^ BIT(7)) & 0x80);
		HALMAC_REG_WRITE_8(halmac_adapter, REG_SDIO_HRPWM1, rpwm);
	}

	value8 = HALMAC_REG_READ_8(halmac_adapter, REG_CR);
	if (value8 == 0xEA)
		halmac_adapter->halmac_state.mac_power = HALMAC_MAC_POWER_OFF;
	else
		halmac_adapter->halmac_state.mac_power = HALMAC_MAC_POWER_ON;

	/*Check if power switch is needed*/
	if (halmac_power == HALMAC_MAC_POWER_ON &&
	    halmac_adapter->halmac_state.mac_power == HALMAC_MAC_POWER_ON) {
		HALMAC_RT_TRACE(
			driver_adapter, HALMAC_MSG_PWR, DBG_WARNING,
			"[WARN]halmac_mac_power_switch power state unchange!\n");
		return HALMAC_RET_PWR_UNCHANGE;
	}

	imr_backup = HALMAC_REG_READ_32(halmac_adapter, REG_SDIO_HIMR);
	HALMAC_REG_WRITE_32(halmac_adapter, REG_SDIO_HIMR, 0);

	if (halmac_power == HALMAC_MAC_POWER_OFF) {
		if (halmac_pwr_seq_parser_88xx(
			    halmac_adapter, HALMAC_PWR_CUT_ALL_MSK,
			    HALMAC_PWR_FAB_TSMC_MSK, interface_mask,
			    halmac_8822b_card_disable_flow) !=
		    HALMAC_RET_SUCCESS) {
			pr_err("[ERR]Handle power off cmd error\n");
			HALMAC_REG_WRITE_32(halmac_adapter, REG_SDIO_HIMR,
					    imr_backup);
			return HALMAC_RET_POWER_OFF_FAIL;
		}

		halmac_adapter->halmac_state.mac_power = HALMAC_MAC_POWER_OFF;
		halmac_adapter->halmac_state.ps_state =
			HALMAC_PS_STATE_UNDEFINE;
		halmac_adapter->halmac_state.dlfw_state = HALMAC_DLFW_NONE;
		halmac_init_adapter_dynamic_para_88xx(halmac_adapter);
	} else {
		if (halmac_pwr_seq_parser_88xx(
			    halmac_adapter, HALMAC_PWR_CUT_ALL_MSK,
			    HALMAC_PWR_FAB_TSMC_MSK, interface_mask,
			    halmac_8822b_card_enable_flow) !=
		    HALMAC_RET_SUCCESS) {
			pr_err("[ERR]Handle power on cmd error\n");
			HALMAC_REG_WRITE_32(halmac_adapter, REG_SDIO_HIMR,
					    imr_backup);
			return HALMAC_RET_POWER_ON_FAIL;
		}

		halmac_adapter->halmac_state.mac_power = HALMAC_MAC_POWER_ON;
		halmac_adapter->halmac_state.ps_state = HALMAC_PS_STATE_ACT;
	}

	HALMAC_REG_WRITE_32(halmac_adapter, REG_SDIO_HIMR, imr_backup);

	HALMAC_RT_TRACE(
		driver_adapter, HALMAC_MSG_PWR, DBG_DMESG,
		"[TRACE]halmac_mac_power_switch_88xx_sdio <==========\n");

	return HALMAC_RET_SUCCESS;
}