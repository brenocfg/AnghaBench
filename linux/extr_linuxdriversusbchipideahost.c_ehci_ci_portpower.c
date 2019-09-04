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
struct TYPE_3__ {struct device* controller; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct ehci_hcd {int /*<<< orphan*/  hcs_params; scalar_t__ priv; } ;
struct ehci_ci_priv {scalar_t__ reg_vbus; } ;
struct device {int dummy; } ;
struct ci_hdrc {TYPE_2__* platdata; } ;
struct TYPE_4__ {scalar_t__ phy_mode; } ;

/* Variables and functions */
 int HCS_N_PORTS (int /*<<< orphan*/ ) ; 
 scalar_t__ USBPHY_INTERFACE_MODE_HSIC ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,int) ; 
 struct ci_hdrc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  hw_port_test_set (struct ci_hdrc*,int) ; 
 int regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 

__attribute__((used)) static int ehci_ci_portpower(struct usb_hcd *hcd, int portnum, bool enable)
{
	struct ehci_hcd *ehci = hcd_to_ehci(hcd);
	struct ehci_ci_priv *priv = (struct ehci_ci_priv *)ehci->priv;
	struct device *dev = hcd->self.controller;
	struct ci_hdrc *ci = dev_get_drvdata(dev);
	int ret = 0;
	int port = HCS_N_PORTS(ehci->hcs_params);

	if (priv->reg_vbus) {
		if (port > 1) {
			dev_warn(dev,
				"Not support multi-port regulator control\n");
			return 0;
		}
		if (enable)
			ret = regulator_enable(priv->reg_vbus);
		else
			ret = regulator_disable(priv->reg_vbus);
		if (ret) {
			dev_err(dev,
				"Failed to %s vbus regulator, ret=%d\n",
				enable ? "enable" : "disable", ret);
			return ret;
		}
	}

	if (enable && (ci->platdata->phy_mode == USBPHY_INTERFACE_MODE_HSIC)) {
		/*
		 * Marvell 28nm HSIC PHY requires forcing the port to HS mode.
		 * As HSIC is always HS, this should be safe for others.
		 */
		hw_port_test_set(ci, 5);
		hw_port_test_set(ci, 0);
	}
	return 0;
}