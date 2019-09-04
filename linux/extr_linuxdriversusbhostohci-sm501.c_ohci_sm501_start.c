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
struct TYPE_2__ {int /*<<< orphan*/  bus_name; struct device* controller; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hcd_to_ohci (struct usb_hcd*) ; 
 int ohci_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci_stop (struct usb_hcd*) ; 

__attribute__((used)) static int ohci_sm501_start(struct usb_hcd *hcd)
{
	struct device *dev = hcd->self.controller;
	int ret;

	ret = ohci_run(hcd_to_ohci(hcd));
	if (ret < 0) {
		dev_err(dev, "can't start %s", hcd->self.bus_name);
		ohci_stop(hcd);
	}

	return ret;
}