#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net2280 {int wakeup_enable; int softconnect; TYPE_3__* usb; TYPE_2__* regs; TYPE_1__* epregs; scalar_t__ bug7734_patched; } ;
struct TYPE_6__ {int /*<<< orphan*/  usbctl; int /*<<< orphan*/  stdrsp; } ;
struct TYPE_5__ {int /*<<< orphan*/  pciirqenb1; int /*<<< orphan*/  pciirqenb0; } ;
struct TYPE_4__ {int /*<<< orphan*/  ep_rsp; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR_NAK_OUT_PACKETS_MODE ; 
 int /*<<< orphan*/  DEVICE_REMOTE_WAKEUP_ENABLE ; 
 int /*<<< orphan*/  ENDPOINT_0_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  GET_DEVICE_STATUS ; 
 int /*<<< orphan*/  GET_INTERFACE_STATUS ; 
 int /*<<< orphan*/  PCI_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  ROOT_PORT_RESET_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  SETUP_PACKET_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  SET_ADDRESS ; 
 int /*<<< orphan*/  SET_EP_HIDE_STATUS_PHASE ; 
 int /*<<< orphan*/  SET_ISOCHRONOUS_DELAY ; 
 int /*<<< orphan*/  SET_SEL ; 
 int /*<<< orphan*/  SET_TEST_MODE ; 
 int /*<<< orphan*/  SUSPEND_REQUEST_CHANGE_INTERRUPT_ENABLE ; 
 int USB_DETECT_ENABLE ; 
 int /*<<< orphan*/  USB_ROOT_PORT_WAKEUP_ENABLE ; 
 int /*<<< orphan*/  VBUS_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ep0_start_338x(struct net2280 *dev)
{

	if (dev->bug7734_patched)
		writel(BIT(CLEAR_NAK_OUT_PACKETS_MODE) |
		       BIT(SET_EP_HIDE_STATUS_PHASE),
		       &dev->epregs[0].ep_rsp);

	/*
	 * hardware optionally handles a bunch of standard requests
	 * that the API hides from drivers anyway.  have it do so.
	 * endpoint status/features are handled in software, to
	 * help pass tests for some dubious behavior.
	 */
	writel(BIT(SET_ISOCHRONOUS_DELAY) |
	       BIT(SET_SEL) |
	       BIT(SET_TEST_MODE) |
	       BIT(SET_ADDRESS) |
	       BIT(GET_INTERFACE_STATUS) |
	       BIT(GET_DEVICE_STATUS),
		&dev->usb->stdrsp);
	dev->wakeup_enable = 1;
	writel(BIT(USB_ROOT_PORT_WAKEUP_ENABLE) |
	       (dev->softconnect << USB_DETECT_ENABLE) |
	       BIT(DEVICE_REMOTE_WAKEUP_ENABLE),
	       &dev->usb->usbctl);

	/* enable irqs so we can see ep0 and general operation  */
	writel(BIT(SETUP_PACKET_INTERRUPT_ENABLE) |
	       BIT(ENDPOINT_0_INTERRUPT_ENABLE),
	       &dev->regs->pciirqenb0);
	writel(BIT(PCI_INTERRUPT_ENABLE) |
	       BIT(ROOT_PORT_RESET_INTERRUPT_ENABLE) |
	       BIT(SUSPEND_REQUEST_CHANGE_INTERRUPT_ENABLE) |
	       BIT(VBUS_INTERRUPT_ENABLE),
	       &dev->regs->pciirqenb1);

	/* don't leave any writes posted */
	(void)readl(&dev->usb->usbctl);
}