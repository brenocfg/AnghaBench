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
typedef  int u8 ;
struct adapter {int /*<<< orphan*/  bFWReady; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*) ; 
 int /*<<< orphan*/  REG_SYS_CFG ; 
 int SW_OFFLOAD_EN ; 
 int /*<<< orphan*/  _8051Reset88E (struct adapter*) ; 
 int usb_read8 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,int /*<<< orphan*/ ,int) ; 

void iol_mode_enable(struct adapter *padapter, u8 enable)
{
	u8 reg_0xf0 = 0;

	if (enable) {
		/* Enable initial offload */
		reg_0xf0 = usb_read8(padapter, REG_SYS_CFG);
		usb_write8(padapter, REG_SYS_CFG, reg_0xf0|SW_OFFLOAD_EN);

		if (!padapter->bFWReady) {
			DBG_88E("bFWReady == false call reset 8051...\n");
			_8051Reset88E(padapter);
		}

	} else {
		/* disable initial offload */
		reg_0xf0 = usb_read8(padapter, REG_SYS_CFG);
		usb_write8(padapter, REG_SYS_CFG, reg_0xf0 & ~SW_OFFLOAD_EN);
	}
}