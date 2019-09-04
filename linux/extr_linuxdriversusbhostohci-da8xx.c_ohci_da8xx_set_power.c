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
struct da8xx_ohci_root_hub {int (* set_power ) (int,int) ;} ;
struct da8xx_ohci_hcd {int reg_enabled; int /*<<< orphan*/  vbus_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct da8xx_ohci_root_hub* dev_get_platdata (struct device*) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int stub1 (int,int) ; 
 struct da8xx_ohci_hcd* to_da8xx_ohci (struct usb_hcd*) ; 

__attribute__((used)) static int ohci_da8xx_set_power(struct usb_hcd *hcd, int on)
{
	struct da8xx_ohci_hcd *da8xx_ohci = to_da8xx_ohci(hcd);
	struct device *dev		= hcd->self.controller;
	struct da8xx_ohci_root_hub *hub	= dev_get_platdata(dev);
	int ret;

	if (hub && hub->set_power)
		return hub->set_power(1, on);

	if (!da8xx_ohci->vbus_reg)
		return 0;

	if (on && !da8xx_ohci->reg_enabled) {
		ret = regulator_enable(da8xx_ohci->vbus_reg);
		if (ret) {
			dev_err(dev, "Failed to enable regulator: %d\n", ret);
			return ret;
		}
		da8xx_ohci->reg_enabled = 1;

	} else if (!on && da8xx_ohci->reg_enabled) {
		ret = regulator_disable(da8xx_ohci->vbus_reg);
		if (ret) {
			dev_err(dev, "Failed  to disable regulator: %d\n", ret);
			return ret;
		}
		da8xx_ohci->reg_enabled = 0;
	}

	return 0;
}