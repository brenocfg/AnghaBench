#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {int rsrc_start; TYPE_1__ self; scalar_t__ regs; scalar_t__ power_budget; int /*<<< orphan*/  rsrc_len; } ;
struct resource {int start; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct fsl_usb2_platform_data {scalar_t__ operating_mode; scalar_t__ controller_ver; int /*<<< orphan*/  (* exit ) (struct platform_device*) ;scalar_t__ has_fsl_erratum_a007792; scalar_t__ have_sysif_regs; scalar_t__ (* init ) (struct platform_device*) ;scalar_t__ power_budget; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_REGISTER_W1C_MASK ; 
 int CTRL_UTMI_PHY_EN ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ FSL_SOC_USB_CTRL ; 
 scalar_t__ FSL_SOC_USB_PORTSC1 ; 
 scalar_t__ FSL_USB2_DR_HOST ; 
 scalar_t__ FSL_USB2_DR_OTG ; 
 scalar_t__ FSL_USB2_MPH_HOST ; 
 scalar_t__ FSL_USB_VER_1_6 ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  PORT_PTS_UTMI ; 
 int PTR_ERR (scalar_t__) ; 
 struct usb_hcd* __usb_create_hcd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clrsetbits_be32 (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int /*<<< orphan*/ ,...) ; 
 struct fsl_usb2_platform_data* dev_get_platdata (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int /*<<< orphan*/  fsl_ehci_hc_driver ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 scalar_t__ stub1 (struct platform_device*) ; 
 int /*<<< orphan*/  stub2 (struct platform_device*) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int fsl_ehci_drv_probe(struct platform_device *pdev)
{
	struct fsl_usb2_platform_data *pdata;
	struct usb_hcd *hcd;
	struct resource *res;
	int irq;
	int retval;

	pr_debug("initializing FSL-SOC USB Controller\n");

	/* Need platform data for setup */
	pdata = dev_get_platdata(&pdev->dev);
	if (!pdata) {
		dev_err(&pdev->dev,
			"No platform data for %s.\n", dev_name(&pdev->dev));
		return -ENODEV;
	}

	/*
	 * This is a host mode driver, verify that we're supposed to be
	 * in host mode.
	 */
	if (!((pdata->operating_mode == FSL_USB2_DR_HOST) ||
	      (pdata->operating_mode == FSL_USB2_MPH_HOST) ||
	      (pdata->operating_mode == FSL_USB2_DR_OTG))) {
		dev_err(&pdev->dev,
			"Non Host Mode configured for %s. Wrong driver linked.\n",
			dev_name(&pdev->dev));
		return -ENODEV;
	}

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res) {
		dev_err(&pdev->dev,
			"Found HC with no IRQ. Check %s setup!\n",
			dev_name(&pdev->dev));
		return -ENODEV;
	}
	irq = res->start;

	hcd = __usb_create_hcd(&fsl_ehci_hc_driver, pdev->dev.parent,
			       &pdev->dev, dev_name(&pdev->dev), NULL);
	if (!hcd) {
		retval = -ENOMEM;
		goto err1;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(hcd->regs)) {
		retval = PTR_ERR(hcd->regs);
		goto err2;
	}

	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	pdata->regs = hcd->regs;

	if (pdata->power_budget)
		hcd->power_budget = pdata->power_budget;

	/*
	 * do platform specific init: check the clock, grab/config pins, etc.
	 */
	if (pdata->init && pdata->init(pdev)) {
		retval = -ENODEV;
		goto err2;
	}

	/* Enable USB controller, 83xx or 8536 */
	if (pdata->have_sysif_regs && pdata->controller_ver < FSL_USB_VER_1_6)
		clrsetbits_be32(hcd->regs + FSL_SOC_USB_CTRL,
				CONTROL_REGISTER_W1C_MASK, 0x4);

	/*
	 * Enable UTMI phy and program PTS field in UTMI mode before asserting
	 * controller reset for USB Controller version 2.5
	 */
	if (pdata->has_fsl_erratum_a007792) {
		clrsetbits_be32(hcd->regs + FSL_SOC_USB_CTRL,
				CONTROL_REGISTER_W1C_MASK, CTRL_UTMI_PHY_EN);
		writel(PORT_PTS_UTMI, hcd->regs + FSL_SOC_USB_PORTSC1);
	}

	/* Don't need to set host mode here. It will be done by tdi_reset() */

	retval = usb_add_hcd(hcd, irq, IRQF_SHARED);
	if (retval != 0)
		goto err2;
	device_wakeup_enable(hcd->self.controller);

#ifdef CONFIG_USB_OTG
	if (pdata->operating_mode == FSL_USB2_DR_OTG) {
		struct ehci_hcd *ehci = hcd_to_ehci(hcd);

		hcd->usb_phy = usb_get_phy(USB_PHY_TYPE_USB2);
		dev_dbg(&pdev->dev, "hcd=0x%p  ehci=0x%p, phy=0x%p\n",
			hcd, ehci, hcd->usb_phy);

		if (!IS_ERR_OR_NULL(hcd->usb_phy)) {
			retval = otg_set_host(hcd->usb_phy->otg,
					      &ehci_to_hcd(ehci)->self);
			if (retval) {
				usb_put_phy(hcd->usb_phy);
				goto err2;
			}
		} else {
			dev_err(&pdev->dev, "can't find phy\n");
			retval = -ENODEV;
			goto err2;
		}

		hcd->skip_phy_initialization = 1;
	}
#endif
	return retval;

      err2:
	usb_put_hcd(hcd);
      err1:
	dev_err(&pdev->dev, "init %s fail, %d\n", dev_name(&pdev->dev), retval);
	if (pdata->exit)
		pdata->exit(pdev);
	return retval;
}