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
struct halmac_p2pps {int dummy; } ;
struct TYPE_2__ {int h2c_version; } ;
struct halmac_adapter {void* driver_adapter; TYPE_1__ fw_version; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int HALMAC_RET_ADAPTER_INVALID ; 
 int HALMAC_RET_API_INVALID ; 
 int HALMAC_RET_FW_NO_SUPPORT ; 
 int HALMAC_RET_NO_DLFW ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 scalar_t__ halmac_adapter_validate (struct halmac_adapter*) ; 
 scalar_t__ halmac_api_validate (struct halmac_adapter*) ; 
 int halmac_func_p2pps_88xx (struct halmac_adapter*,struct halmac_p2pps*) ; 
 scalar_t__ halmac_fw_validate (struct halmac_adapter*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

enum halmac_ret_status halmac_p2pps_88xx(struct halmac_adapter *halmac_adapter,
					 struct halmac_p2pps *p2p_ps)
{
	void *driver_adapter = NULL;
	enum halmac_ret_status status = HALMAC_RET_SUCCESS;

	if (halmac_adapter_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_ADAPTER_INVALID;

	if (halmac_api_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_API_INVALID;

	if (halmac_fw_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_NO_DLFW;

	if (halmac_adapter->fw_version.h2c_version < 6)
		return HALMAC_RET_FW_NO_SUPPORT;

	driver_adapter = halmac_adapter->driver_adapter;

	status = halmac_func_p2pps_88xx(halmac_adapter, p2p_ps);

	if (status != HALMAC_RET_SUCCESS) {
		pr_err("[ERR]halmac_p2pps FAIL = %x!!\n", status);
		return status;
	}

	return HALMAC_RET_SUCCESS;
}