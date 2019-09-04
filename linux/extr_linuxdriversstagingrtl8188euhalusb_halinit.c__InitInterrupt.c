#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct adapter {TYPE_1__* HalData; } ;
struct TYPE_4__ {int /*<<< orphan*/  ishighspeed; } ;
struct TYPE_3__ {int* IntrMask; } ;

/* Variables and functions */
 int IMR_CPWM2_88E ; 
 int IMR_CPWM_88E ; 
 int IMR_PSTIMEOUT_88E ; 
 int IMR_RXERR_88E ; 
 int IMR_RXFOVW_88E ; 
 int IMR_TBDER_88E ; 
 int IMR_TXERR_88E ; 
 int IMR_TXFOVW_88E ; 
 int INT_BULK_SEL ; 
 int /*<<< orphan*/  REG_HIMRE_88E ; 
 int /*<<< orphan*/  REG_HIMR_88E ; 
 int /*<<< orphan*/  REG_HISR_88E ; 
 int /*<<< orphan*/  REG_USB_SPECIAL_OPTION ; 
 TYPE_2__* adapter_to_dvobj (struct adapter*) ; 
 int usb_read8 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write32 (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _InitInterrupt(struct adapter *Adapter)
{
	u32 imr, imr_ex;
	u8  usb_opt;

	/* HISR write one to clear */
	usb_write32(Adapter, REG_HISR_88E, 0xFFFFFFFF);
	/*  HIMR - */
	imr = IMR_PSTIMEOUT_88E | IMR_TBDER_88E | IMR_CPWM_88E | IMR_CPWM2_88E;
	usb_write32(Adapter, REG_HIMR_88E, imr);
	Adapter->HalData->IntrMask[0] = imr;

	imr_ex = IMR_TXERR_88E | IMR_RXERR_88E | IMR_TXFOVW_88E | IMR_RXFOVW_88E;
	usb_write32(Adapter, REG_HIMRE_88E, imr_ex);
	Adapter->HalData->IntrMask[1] = imr_ex;

	/*  REG_USB_SPECIAL_OPTION - BIT(4) */
	/*  0; Use interrupt endpoint to upload interrupt pkt */
	/*  1; Use bulk endpoint to upload interrupt pkt, */
	usb_opt = usb_read8(Adapter, REG_USB_SPECIAL_OPTION);

	if (!adapter_to_dvobj(Adapter)->ishighspeed)
		usb_opt = usb_opt & (~INT_BULK_SEL);
	else
		usb_opt = usb_opt | (INT_BULK_SEL);

	usb_write8(Adapter, REG_USB_SPECIAL_OPTION, usb_opt);
}