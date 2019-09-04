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
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {int /*<<< orphan*/  regs; TYPE_1__ self; } ;
struct isp1760_hcd {int hcs_params; } ;

/* Variables and functions */
 int ALL_ATX_RESET ; 
 int ENODEV ; 
 int /*<<< orphan*/  HC_ATL_PTD_SKIPMAP_REG ; 
 int /*<<< orphan*/  HC_BUFFER_STATUS_REG ; 
 int /*<<< orphan*/  HC_CHIP_ID_REG ; 
 int /*<<< orphan*/  HC_HCSPARAMS ; 
 int /*<<< orphan*/  HC_HW_MODE_CTRL ; 
 int /*<<< orphan*/  HC_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  HC_INT_PTD_SKIPMAP_REG ; 
 int /*<<< orphan*/  HC_ISO_PTD_SKIPMAP_REG ; 
 int /*<<< orphan*/  HC_SCRATCH_REG ; 
 int INTERRUPT_ENABLE_MASK ; 
 int NO_TRANSFER_ACTIVE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ehci_reset (struct usb_hcd*) ; 
 struct isp1760_hcd* hcd_to_priv (struct usb_hcd*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int priv_init (struct usb_hcd*) ; 
 int reg_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int isp1760_hc_setup(struct usb_hcd *hcd)
{
	struct isp1760_hcd *priv = hcd_to_priv(hcd);
	int result;
	u32 scratch, hwmode;

	reg_write32(hcd->regs, HC_SCRATCH_REG, 0xdeadbabe);
	/* Change bus pattern */
	scratch = reg_read32(hcd->regs, HC_CHIP_ID_REG);
	scratch = reg_read32(hcd->regs, HC_SCRATCH_REG);
	if (scratch != 0xdeadbabe) {
		dev_err(hcd->self.controller, "Scratch test failed.\n");
		return -ENODEV;
	}

	/*
	 * The RESET_HC bit in the SW_RESET register is supposed to reset the
	 * host controller without touching the CPU interface registers, but at
	 * least on the ISP1761 it seems to behave as the RESET_ALL bit and
	 * reset the whole device. We thus can't use it here, so let's reset
	 * the host controller through the EHCI USB Command register. The device
	 * has been reset in core code anyway, so this shouldn't matter.
	 */
	reg_write32(hcd->regs, HC_BUFFER_STATUS_REG, 0);
	reg_write32(hcd->regs, HC_ATL_PTD_SKIPMAP_REG, NO_TRANSFER_ACTIVE);
	reg_write32(hcd->regs, HC_INT_PTD_SKIPMAP_REG, NO_TRANSFER_ACTIVE);
	reg_write32(hcd->regs, HC_ISO_PTD_SKIPMAP_REG, NO_TRANSFER_ACTIVE);

	result = ehci_reset(hcd);
	if (result)
		return result;

	/* Step 11 passed */

	/* ATL reset */
	hwmode = reg_read32(hcd->regs, HC_HW_MODE_CTRL) & ~ALL_ATX_RESET;
	reg_write32(hcd->regs, HC_HW_MODE_CTRL, hwmode | ALL_ATX_RESET);
	mdelay(10);
	reg_write32(hcd->regs, HC_HW_MODE_CTRL, hwmode);

	reg_write32(hcd->regs, HC_INTERRUPT_ENABLE, INTERRUPT_ENABLE_MASK);

	priv->hcs_params = reg_read32(hcd->regs, HC_HCSPARAMS);

	return priv_init(hcd);
}