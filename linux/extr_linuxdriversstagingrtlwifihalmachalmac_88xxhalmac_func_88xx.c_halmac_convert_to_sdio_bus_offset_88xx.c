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
struct halmac_adapter {void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int HALMAC_RET_CONVERT_SDIO_OFFSET_FAIL ; 
 int HALMAC_RET_SUCCESS ; 
 int HALMAC_SDIO_CMD_ADDR_MAC_REG ; 
 int HALMAC_SDIO_CMD_ADDR_SDIO_REG ; 
 int HALMAC_SDIO_LOCAL_MSK ; 
 int HALMAC_WLAN_MAC_REG_MSK ; 
#define  SDIO_LOCAL_OFFSET 129 
#define  WLAN_IOREG_OFFSET 128 
 int /*<<< orphan*/  pr_err (char*) ; 

enum halmac_ret_status
halmac_convert_to_sdio_bus_offset_88xx(struct halmac_adapter *halmac_adapter,
				       u32 *halmac_offset)
{
	void *driver_adapter = NULL;

	driver_adapter = halmac_adapter->driver_adapter;

	switch ((*halmac_offset) & 0xFFFF0000) {
	case WLAN_IOREG_OFFSET:
		*halmac_offset = (HALMAC_SDIO_CMD_ADDR_MAC_REG << 13) |
				 (*halmac_offset & HALMAC_WLAN_MAC_REG_MSK);
		break;
	case SDIO_LOCAL_OFFSET:
		*halmac_offset = (HALMAC_SDIO_CMD_ADDR_SDIO_REG << 13) |
				 (*halmac_offset & HALMAC_SDIO_LOCAL_MSK);
		break;
	default:
		*halmac_offset = 0xFFFFFFFF;
		pr_err("Unknown base address!!\n");
		return HALMAC_RET_CONVERT_SDIO_OFFSET_FAIL;
	}

	return HALMAC_RET_SUCCESS;
}