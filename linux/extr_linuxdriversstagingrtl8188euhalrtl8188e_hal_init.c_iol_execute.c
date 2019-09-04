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
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  REG_HMEBOX_E0 ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 unsigned long jiffies ; 
 int jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int usb_read8 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,int /*<<< orphan*/ ,int) ; 

s32 iol_execute(struct adapter *padapter, u8 control)
{
	s32 status = _FAIL;
	u8 reg_0x88 = 0;
	unsigned long start = 0;

	control = control&0x0f;
	reg_0x88 = usb_read8(padapter, REG_HMEBOX_E0);
	usb_write8(padapter, REG_HMEBOX_E0,  reg_0x88|control);

	start = jiffies;
	while ((reg_0x88 = usb_read8(padapter, REG_HMEBOX_E0)) & control &&
	       jiffies_to_msecs(jiffies - start) < 1000) {
		udelay(5);
	}

	reg_0x88 = usb_read8(padapter, REG_HMEBOX_E0);
	status = (reg_0x88 & control) ? _FAIL : _SUCCESS;
	if (reg_0x88 & control<<4)
		status = _FAIL;
	return status;
}