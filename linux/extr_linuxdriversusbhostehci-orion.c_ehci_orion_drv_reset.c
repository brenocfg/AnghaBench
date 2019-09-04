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
struct TYPE_2__ {struct device* controller; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_SBUSCFG ; 
 int /*<<< orphan*/  USB_SBUSCFG_DEF_VAL ; 
 int ehci_setup (struct usb_hcd*) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ehci_orion_drv_reset(struct usb_hcd *hcd)
{
	struct device *dev = hcd->self.controller;
	int ret;

	ret = ehci_setup(hcd);
	if (ret)
		return ret;

	/*
	 * For SoC without hlock, need to program sbuscfg value to guarantee
	 * AHB master's burst would not overrun or underrun FIFO.
	 *
	 * sbuscfg reg has to be set after usb controller reset, otherwise
	 * the value would be override to 0.
	 */
	if (of_device_is_compatible(dev->of_node, "marvell,armada-3700-ehci"))
		wrl(USB_SBUSCFG, USB_SBUSCFG_DEF_VAL);

	return ret;
}