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
struct usb_hcd {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int CMD_RUN ; 
 int /*<<< orphan*/  HC_HW_MODE_CTRL ; 
 int /*<<< orphan*/  HC_USBCMD ; 
 int HW_GLOBAL_INTR_EN ; 
 int /*<<< orphan*/  isp1760_stop (struct usb_hcd*) ; 
 int reg_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void isp1760_shutdown(struct usb_hcd *hcd)
{
	u32 command, temp;

	isp1760_stop(hcd);
	temp = reg_read32(hcd->regs, HC_HW_MODE_CTRL);
	reg_write32(hcd->regs, HC_HW_MODE_CTRL, temp &= ~HW_GLOBAL_INTR_EN);

	command = reg_read32(hcd->regs, HC_USBCMD);
	command &= ~CMD_RUN;
	reg_write32(hcd->regs, HC_USBCMD, command);
}