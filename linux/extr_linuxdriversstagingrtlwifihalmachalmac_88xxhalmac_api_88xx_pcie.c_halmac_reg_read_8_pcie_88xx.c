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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_api; void* driver_adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  HALMAC_RET_ADAPTER_INVALID ; 
 int /*<<< orphan*/  HALMAC_RET_API_INVALID ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  PLATFORM_REG_READ_8 (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ halmac_adapter_validate (struct halmac_adapter*) ; 
 scalar_t__ halmac_api_validate (struct halmac_adapter*) ; 

u8 halmac_reg_read_8_pcie_88xx(struct halmac_adapter *halmac_adapter,
			       u32 halmac_offset)
{
	void *driver_adapter = NULL;
	struct halmac_api *halmac_api;

	if (halmac_adapter_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_ADAPTER_INVALID;

	if (halmac_api_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_API_INVALID;

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	return PLATFORM_REG_READ_8(driver_adapter, halmac_offset);
}