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
struct adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int FWDL_ChkSum_rpt ; 
 int /*<<< orphan*/  FW_8192C_POLLING_DELAY ; 
 int MCUFWDL_RDY ; 
 scalar_t__ POLLING_READY_TIMEOUT_COUNT ; 
 int /*<<< orphan*/  REG_MCUFWDL ; 
 int WINTINI_RDY ; 
 int /*<<< orphan*/  rtl88e_firmware_selfreset (struct adapter*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int usb_read32 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write32 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int _rtl88e_fw_free_to_go(struct adapter *adapt)
{
	int err = -EIO;
	u32 counter = 0;
	u32 value32;

	do {
		value32 = usb_read32(adapt, REG_MCUFWDL);
		if (value32 & FWDL_ChkSum_rpt)
			break;
	} while (counter++ < POLLING_READY_TIMEOUT_COUNT);

	if (counter >= POLLING_READY_TIMEOUT_COUNT)
		goto exit;

	value32 = usb_read32(adapt, REG_MCUFWDL);
	value32 |= MCUFWDL_RDY;
	value32 &= ~WINTINI_RDY;
	usb_write32(adapt, REG_MCUFWDL, value32);

	rtl88e_firmware_selfreset(adapt);
	counter = 0;

	do {
		value32 = usb_read32(adapt, REG_MCUFWDL);
		if (value32 & WINTINI_RDY) {
			err = 0;
			goto exit;
		}

		udelay(FW_8192C_POLLING_DELAY);

	} while (counter++ < POLLING_READY_TIMEOUT_COUNT);

exit:
	return err;
}