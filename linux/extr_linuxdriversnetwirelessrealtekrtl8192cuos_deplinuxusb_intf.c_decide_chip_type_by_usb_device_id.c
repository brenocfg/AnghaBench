#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_device_id {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  chip_type; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_CHIP_TYPE ; 

__attribute__((used)) static void decide_chip_type_by_usb_device_id(_adapter *padapter, const struct usb_device_id *pdid)
{
	padapter->chip_type = NULL_CHIP_TYPE;
#ifdef CONFIG_RTL8192C
	padapter->chip_type = RTL8188C_8192C;
	padapter->HardwareType = HARDWARE_TYPE_RTL8192CU;
	DBG_871X("CHIP TYPE: RTL8188C_8192C\n");
#endif

#ifdef CONFIG_RTL8192D
	padapter->chip_type = RTL8192D;
	padapter->HardwareType = HARDWARE_TYPE_RTL8192DU;
	DBG_871X("CHIP TYPE: RTL8192D\n");
#endif
}