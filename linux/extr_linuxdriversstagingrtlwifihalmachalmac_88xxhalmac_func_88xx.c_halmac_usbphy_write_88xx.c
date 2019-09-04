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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_api; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,int,int) ; 
 int HALMAC_RET_NOT_SUPPORT ; 
 int HALMAC_RET_SUCCESS ; 
 scalar_t__ HAL_INTF_PHY_USB2 ; 
 scalar_t__ HAL_INTF_PHY_USB3 ; 
 int /*<<< orphan*/  pr_err (char*) ; 

enum halmac_ret_status
halmac_usbphy_write_88xx(struct halmac_adapter *halmac_adapter, u8 addr,
			 u16 data, u8 speed)
{
	void *driver_adapter = NULL;
	struct halmac_api *halmac_api;

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	if (speed == HAL_INTF_PHY_USB3) {
		HALMAC_REG_WRITE_8(halmac_adapter, 0xff0d, (u8)data);
		HALMAC_REG_WRITE_8(halmac_adapter, 0xff0e, (u8)(data >> 8));
		HALMAC_REG_WRITE_8(halmac_adapter, 0xff0c, addr | BIT(7));
	} else if (speed == HAL_INTF_PHY_USB2) {
		HALMAC_REG_WRITE_8(halmac_adapter, 0xfe41, (u8)data);
		HALMAC_REG_WRITE_8(halmac_adapter, 0xfe40, addr);
		HALMAC_REG_WRITE_8(halmac_adapter, 0xfe42, 0x81);
	} else {
		pr_err("[ERR]Error USB Speed !\n");
		return HALMAC_RET_NOT_SUPPORT;
	}

	return HALMAC_RET_SUCCESS;
}