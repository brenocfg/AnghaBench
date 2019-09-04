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
typedef  int /*<<< orphan*/  u32 ;
struct usb_hcd {int /*<<< orphan*/  regs; } ;
struct isp1760_hcd {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPortFeature ; 
 int /*<<< orphan*/  HC_CONFIGFLAG ; 
 int /*<<< orphan*/  HC_HW_MODE_CTRL ; 
 int /*<<< orphan*/  HW_GLOBAL_INTR_EN ; 
 int /*<<< orphan*/  USB_PORT_FEAT_POWER ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_reset (struct usb_hcd*) ; 
 int /*<<< orphan*/  errata2_timer ; 
 struct isp1760_hcd* hcd_to_priv (struct usb_hcd*) ; 
 int /*<<< orphan*/  isp1760_hub_control (struct usb_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isp1760_stop(struct usb_hcd *hcd)
{
	struct isp1760_hcd *priv = hcd_to_priv(hcd);
	u32 temp;

	del_timer(&errata2_timer);

	isp1760_hub_control(hcd, ClearPortFeature, USB_PORT_FEAT_POWER,	1,
			NULL, 0);
	msleep(20);

	spin_lock_irq(&priv->lock);
	ehci_reset(hcd);
	/* Disable IRQ */
	temp = reg_read32(hcd->regs, HC_HW_MODE_CTRL);
	reg_write32(hcd->regs, HC_HW_MODE_CTRL, temp &= ~HW_GLOBAL_INTR_EN);
	spin_unlock_irq(&priv->lock);

	reg_write32(hcd->regs, HC_CONFIGFLAG, 0);
}