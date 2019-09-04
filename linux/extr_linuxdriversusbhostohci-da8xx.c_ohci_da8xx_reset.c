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
typedef  int u32 ;
struct TYPE_4__ {struct device* controller; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct ohci_hcd {int num_ports; TYPE_3__* regs; } ;
struct device {int dummy; } ;
struct da8xx_ohci_root_hub {int potpgt; } ;
struct TYPE_5__ {int /*<<< orphan*/  a; } ;
struct TYPE_6__ {TYPE_2__ roothub; } ;

/* Variables and functions */
 int RH_A_NOCP ; 
 int RH_A_NPS ; 
 int RH_A_OCPM ; 
 int RH_A_POTPGT ; 
 int RH_A_PSM ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct da8xx_ohci_root_hub* dev_get_platdata (struct device*) ; 
 struct ohci_hcd* hcd_to_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  ohci_da8xx_disable (struct usb_hcd*) ; 
 int ohci_da8xx_enable (struct usb_hcd*) ; 
 scalar_t__ ohci_da8xx_has_oci (struct usb_hcd*) ; 
 scalar_t__ ohci_da8xx_has_potpgt (struct usb_hcd*) ; 
 scalar_t__ ohci_da8xx_has_set_power (struct usb_hcd*) ; 
 int ohci_readl (struct ohci_hcd*,int /*<<< orphan*/ *) ; 
 int ohci_setup (struct usb_hcd*) ; 
 int /*<<< orphan*/  ohci_writel (struct ohci_hcd*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ohci_da8xx_reset(struct usb_hcd *hcd)
{
	struct device *dev		= hcd->self.controller;
	struct da8xx_ohci_root_hub *hub	= dev_get_platdata(dev);
	struct ohci_hcd	*ohci		= hcd_to_ohci(hcd);
	int result;
	u32 rh_a;

	dev_dbg(dev, "starting USB controller\n");

	result = ohci_da8xx_enable(hcd);
	if (result < 0)
		return result;

	/*
	 * DA8xx only have 1 port connected to the pins but the HC root hub
	 * register A reports 2 ports, thus we'll have to override it...
	 */
	ohci->num_ports = 1;

	result = ohci_setup(hcd);
	if (result < 0) {
		ohci_da8xx_disable(hcd);
		return result;
	}

	/*
	 * Since we're providing a board-specific root hub port power control
	 * and over-current reporting, we have to override the HC root hub A
	 * register's default value, so that ohci_hub_control() could return
	 * the correct hub descriptor...
	 */
	rh_a = ohci_readl(ohci, &ohci->regs->roothub.a);
	if (ohci_da8xx_has_set_power(hcd)) {
		rh_a &= ~RH_A_NPS;
		rh_a |=  RH_A_PSM;
	}
	if (ohci_da8xx_has_oci(hcd)) {
		rh_a &= ~RH_A_NOCP;
		rh_a |=  RH_A_OCPM;
	}
	if (ohci_da8xx_has_potpgt(hcd)) {
		rh_a &= ~RH_A_POTPGT;
		rh_a |= hub->potpgt << 24;
	}
	ohci_writel(ohci, rh_a, &ohci->regs->roothub.a);

	return result;
}