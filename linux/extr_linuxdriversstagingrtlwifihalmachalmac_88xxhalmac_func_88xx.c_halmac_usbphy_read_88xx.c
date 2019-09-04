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
typedef  scalar_t__ u16 ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_api; void* driver_adapter; } ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int HALMAC_REG_READ_32 (struct halmac_adapter*,int) ; 
 scalar_t__ HALMAC_REG_READ_8 (struct halmac_adapter*,int) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,int,int) ; 
 scalar_t__ HALMAC_RET_NOT_SUPPORT ; 
 scalar_t__ HAL_INTF_PHY_USB2 ; 
 scalar_t__ HAL_INTF_PHY_USB3 ; 
 int /*<<< orphan*/  pr_err (char*) ; 

u16 halmac_usbphy_read_88xx(struct halmac_adapter *halmac_adapter, u8 addr,
			    u8 speed)
{
	void *driver_adapter = NULL;
	struct halmac_api *halmac_api;
	u16 value = 0;

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	if (speed == HAL_INTF_PHY_USB3) {
		HALMAC_REG_WRITE_8(halmac_adapter, 0xff0c, addr | BIT(6));
		value = (u16)(HALMAC_REG_READ_32(halmac_adapter, 0xff0c) >> 8);
	} else if (speed == HAL_INTF_PHY_USB2) {
		if ((addr >= 0xE0) /*&& (addr <= 0xFF)*/)
			addr -= 0x20;
		if ((addr >= 0xC0) && (addr <= 0xDF)) {
			HALMAC_REG_WRITE_8(halmac_adapter, 0xfe40, addr);
			HALMAC_REG_WRITE_8(halmac_adapter, 0xfe42, 0x81);
			value = HALMAC_REG_READ_8(halmac_adapter, 0xfe43);
		} else {
			pr_err("[ERR]Error USB2PHY offset!\n");
			return HALMAC_RET_NOT_SUPPORT;
		}
	} else {
		pr_err("[ERR]Error USB Speed !\n");
		return HALMAC_RET_NOT_SUPPORT;
	}

	return value;
}