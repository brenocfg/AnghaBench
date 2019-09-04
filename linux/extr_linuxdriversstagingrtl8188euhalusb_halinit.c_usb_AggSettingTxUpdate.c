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
typedef  int u32 ;
struct hal_data_8188e {int UsbTxAggMode; int UsbTxAggDescNum; } ;
struct TYPE_2__ {scalar_t__ wifi_spec; } ;
struct adapter {TYPE_1__ registrypriv; struct hal_data_8188e* HalData; } ;

/* Variables and functions */
 int BLK_DESC_NUM_MASK ; 
 int BLK_DESC_NUM_SHIFT ; 
 int /*<<< orphan*/  REG_TDECTRL ; 
 int usb_read32 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write32 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void usb_AggSettingTxUpdate(struct adapter *Adapter)
{
	struct hal_data_8188e *haldata = Adapter->HalData;
	u32 value32;

	if (Adapter->registrypriv.wifi_spec)
		haldata->UsbTxAggMode = false;

	if (haldata->UsbTxAggMode) {
		value32 = usb_read32(Adapter, REG_TDECTRL);
		value32 = value32 & ~(BLK_DESC_NUM_MASK << BLK_DESC_NUM_SHIFT);
		value32 |= ((haldata->UsbTxAggDescNum & BLK_DESC_NUM_MASK) << BLK_DESC_NUM_SHIFT);

		usb_write32(Adapter, REG_TDECTRL, value32);
	}
}