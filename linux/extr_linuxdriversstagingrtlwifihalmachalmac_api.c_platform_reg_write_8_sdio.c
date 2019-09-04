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
typedef  int u32 ;
struct halmac_platform_api {int /*<<< orphan*/  (* SDIO_CMD52_WRITE ) (void*,int,int /*<<< orphan*/ ) ;} ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int HALMAC_RET_SUCCESS ; 
 int WLAN_IOREG_OFFSET ; 
 int halmac_convert_to_sdio_bus_offset (int*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  stub1 (void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum halmac_ret_status
platform_reg_write_8_sdio(void *driver_adapter,
			  struct halmac_platform_api *halmac_platform_api,
			  u32 offset, u8 data)
{
	enum halmac_ret_status status = HALMAC_RET_SUCCESS;
	u32 halmac_offset = offset;

	if ((halmac_offset & 0xFFFF0000) == 0)
		halmac_offset |= WLAN_IOREG_OFFSET;

	status = halmac_convert_to_sdio_bus_offset(&halmac_offset);

	if (status != HALMAC_RET_SUCCESS) {
		pr_err("halmac_reg_write_8_sdio_88xx error = %x\n", status);
		return status;
	}
	halmac_platform_api->SDIO_CMD52_WRITE(driver_adapter, halmac_offset,
					      data);

	return HALMAC_RET_SUCCESS;
}