#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* dev_if; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_9__ {int enumspd; } ;
struct TYPE_11__ {TYPE_3__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_5__ dsts_data_t ;
struct TYPE_8__ {TYPE_1__* dev_global_regs; } ;
struct TYPE_7__ {int /*<<< orphan*/  dsts; } ;

/* Variables and functions */
#define  DWC_DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ 131 
#define  DWC_DSTS_ENUMSPD_FS_PHY_48MHZ 130 
#define  DWC_DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ 129 
#define  DWC_DSTS_ENUMSPD_LS_PHY_6MHZ 128 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int USB_SPEED_FULL ; 
 int USB_SPEED_HIGH ; 
 int USB_SPEED_LOW ; 

__attribute__((used)) static int get_device_speed(dwc_otg_core_if_t * core_if)
{
	dsts_data_t dsts;
	int speed = 0;
	dsts.d32 = DWC_READ_REG32(&core_if->dev_if->dev_global_regs->dsts);

	switch (dsts.b.enumspd) {
	case DWC_DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ:
		speed = USB_SPEED_HIGH;
		break;
	case DWC_DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ:
	case DWC_DSTS_ENUMSPD_FS_PHY_48MHZ:
		speed = USB_SPEED_FULL;
		break;

	case DWC_DSTS_ENUMSPD_LS_PHY_6MHZ:
		speed = USB_SPEED_LOW;
		break;
	}

	return speed;
}