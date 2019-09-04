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
struct da8xx_ohci_root_hub {int (* get_oci ) (int) ;} ;
struct da8xx_ohci_hcd {int /*<<< orphan*/  vbus_reg; } ;

/* Variables and functions */
 unsigned int REGULATOR_ERROR_OVER_CURRENT ; 
 struct da8xx_ohci_root_hub* dev_get_platdata (struct device*) ; 
 int regulator_get_error_flags (int /*<<< orphan*/ ,unsigned int*) ; 
 int stub1 (int) ; 
 struct da8xx_ohci_hcd* to_da8xx_ohci (struct usb_hcd*) ; 

__attribute__((used)) static int ohci_da8xx_get_oci(struct usb_hcd *hcd)
{
	struct da8xx_ohci_hcd *da8xx_ohci = to_da8xx_ohci(hcd);
	struct device *dev		= hcd->self.controller;
	struct da8xx_ohci_root_hub *hub	= dev_get_platdata(dev);
	unsigned int flags;
	int ret;

	if (hub && hub->get_oci)
		return hub->get_oci(1);

	if (!da8xx_ohci->vbus_reg)
		return 0;

	ret = regulator_get_error_flags(da8xx_ohci->vbus_reg, &flags);
	if (ret)
		return ret;

	if (flags & REGULATOR_ERROR_OVER_CURRENT)
		return 1;

	return 0;
}