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
struct device {int dummy; } ;
struct da8xx_ohci_root_hub {scalar_t__ potpgt; } ;

/* Variables and functions */
 struct da8xx_ohci_root_hub* dev_get_platdata (struct device*) ; 

__attribute__((used)) static int ohci_da8xx_has_potpgt(struct usb_hcd *hcd)
{
	struct device *dev		= hcd->self.controller;
	struct da8xx_ohci_root_hub *hub	= dev_get_platdata(dev);

	if (hub && hub->potpgt)
		return 1;

	return 0;
}