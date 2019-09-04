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
typedef  int /*<<< orphan*/  u32 ;
struct udc {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; scalar_t__ connected; int /*<<< orphan*/ * ep; int /*<<< orphan*/  gadget; TYPE_2__* driver; TYPE_1__* regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disconnect ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDC_DEVCTL_SRX_FLUSH ; 
 int UDC_EP_NUM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  empty_req_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udc_mask_unused_interrupts (struct udc*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stop_udc(struct udc *udc)
{
	int tmp;
	u32 reg;

	spin_lock(&udc->lock);

	/* Flush the receieve fifo */
	reg = readl(&udc->regs->ctl);
	reg |= AMD_BIT(UDC_DEVCTL_SRX_FLUSH);
	writel(reg, &udc->regs->ctl);

	reg = readl(&udc->regs->ctl);
	reg &= ~(AMD_BIT(UDC_DEVCTL_SRX_FLUSH));
	writel(reg, &udc->regs->ctl);
	dev_dbg(udc->dev, "ep rx queue flushed\n");

	/* Mask interrupts. Required more so when the
	 * UDC is connected to a DRD phy.
	 */
	udc_mask_unused_interrupts(udc);

	/* Disconnect gadget driver */
	if (udc->driver) {
		spin_unlock(&udc->lock);
		udc->driver->disconnect(&udc->gadget);
		spin_lock(&udc->lock);

		/* empty queues */
		for (tmp = 0; tmp < UDC_EP_NUM; tmp++)
			empty_req_queue(&udc->ep[tmp]);
	}
	udc->connected = 0;

	spin_unlock(&udc->lock);
	dev_info(udc->dev, "Device disconnected\n");
}