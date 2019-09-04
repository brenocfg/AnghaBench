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
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_api; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_intf_phy_platform { ____Placeholder_halmac_intf_phy_platform } halmac_intf_phy_platform ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  HALMAC_API_PHY_CFG ; 
 int /*<<< orphan*/  HALMAC_MSG_PWR ; 
 int HALMAC_RET_ADAPTER_INVALID ; 
 int HALMAC_RET_API_INVALID ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RTL8822B_USB2_PHY ; 
 int /*<<< orphan*/  HALMAC_RTL8822B_USB3_PHY ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HAL_INTF_PHY_USB2 ; 
 int /*<<< orphan*/  HAL_INTF_PHY_USB3 ; 
 scalar_t__ halmac_adapter_validate (struct halmac_adapter*) ; 
 int /*<<< orphan*/  halmac_api_record_id_88xx (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ halmac_api_validate (struct halmac_adapter*) ; 
 int halmac_parse_intf_phy_88xx (struct halmac_adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

enum halmac_ret_status
halmac_phy_cfg_8822b_usb(struct halmac_adapter *halmac_adapter,
			 enum halmac_intf_phy_platform platform)
{
	void *driver_adapter = NULL;
	enum halmac_ret_status status = HALMAC_RET_SUCCESS;
	struct halmac_api *halmac_api;

	if (halmac_adapter_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_ADAPTER_INVALID;

	if (halmac_api_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_API_INVALID;

	halmac_api_record_id_88xx(halmac_adapter, HALMAC_API_PHY_CFG);

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_PWR, DBG_DMESG,
			"halmac_phy_cfg ==========>\n");

	status = halmac_parse_intf_phy_88xx(halmac_adapter,
					    HALMAC_RTL8822B_USB2_PHY, platform,
					    HAL_INTF_PHY_USB2);

	if (status != HALMAC_RET_SUCCESS)
		return status;

	status = halmac_parse_intf_phy_88xx(halmac_adapter,
					    HALMAC_RTL8822B_USB3_PHY, platform,
					    HAL_INTF_PHY_USB3);

	if (status != HALMAC_RET_SUCCESS)
		return status;

	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_PWR, DBG_DMESG,
			"halmac_phy_cfg <==========\n");

	return HALMAC_RET_SUCCESS;
}