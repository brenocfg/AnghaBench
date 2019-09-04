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
struct TYPE_3__ {TYPE_2__* controller; } ;
struct usb_hcd {TYPE_1__ self; int /*<<< orphan*/  rsrc_len; int /*<<< orphan*/  rsrc_start; void* regs; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct ohci_hcd {int /*<<< orphan*/  hc_control; int /*<<< orphan*/  num_ports; } ;
struct ohci_at91_priv {int /*<<< orphan*/  sfr_regmap; void* hclk; void* fclk; void* iclk; } ;
struct hc_driver {int dummy; } ;
struct at91_usbh_data {int /*<<< orphan*/  ports; } ;
struct TYPE_4__ {struct at91_usbh_data* platform_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  OHCI_CTRL_RWC ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  at91_dt_syscon_sfr () ; 
 int /*<<< orphan*/  at91_start_hc (struct platform_device*) ; 
 int /*<<< orphan*/  at91_stop_hc (struct platform_device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  device_wakeup_enable (TYPE_2__*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct ohci_hcd* hcd_to_ohci (struct usb_hcd*) ; 
 struct ohci_at91_priv* hcd_to_ohci_at91_priv (struct usb_hcd*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (struct hc_driver const*,struct device*,char*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int usb_hcd_at91_probe(const struct hc_driver *driver,
			struct platform_device *pdev)
{
	struct at91_usbh_data *board;
	struct ohci_hcd *ohci;
	int retval;
	struct usb_hcd *hcd;
	struct ohci_at91_priv *ohci_at91;
	struct device *dev = &pdev->dev;
	struct resource *res;
	int irq;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_dbg(dev, "hcd probe: missing irq resource\n");
		return irq;
	}

	hcd = usb_create_hcd(driver, dev, "at91");
	if (!hcd)
		return -ENOMEM;
	ohci_at91 = hcd_to_ohci_at91_priv(hcd);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(hcd->regs)) {
		retval = PTR_ERR(hcd->regs);
		goto err;
	}
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	ohci_at91->iclk = devm_clk_get(dev, "ohci_clk");
	if (IS_ERR(ohci_at91->iclk)) {
		dev_err(dev, "failed to get ohci_clk\n");
		retval = PTR_ERR(ohci_at91->iclk);
		goto err;
	}
	ohci_at91->fclk = devm_clk_get(dev, "uhpck");
	if (IS_ERR(ohci_at91->fclk)) {
		dev_err(dev, "failed to get uhpck\n");
		retval = PTR_ERR(ohci_at91->fclk);
		goto err;
	}
	ohci_at91->hclk = devm_clk_get(dev, "hclk");
	if (IS_ERR(ohci_at91->hclk)) {
		dev_err(dev, "failed to get hclk\n");
		retval = PTR_ERR(ohci_at91->hclk);
		goto err;
	}

	ohci_at91->sfr_regmap = at91_dt_syscon_sfr();
	if (!ohci_at91->sfr_regmap)
		dev_dbg(dev, "failed to find sfr node\n");

	board = hcd->self.controller->platform_data;
	ohci = hcd_to_ohci(hcd);
	ohci->num_ports = board->ports;
	at91_start_hc(pdev);

	/*
	 * The RemoteWakeupConnected bit has to be set explicitly
	 * before calling ohci_run. The reset value of this bit is 0.
	 */
	ohci->hc_control = OHCI_CTRL_RWC;

	retval = usb_add_hcd(hcd, irq, IRQF_SHARED);
	if (retval == 0) {
		device_wakeup_enable(hcd->self.controller);
		return retval;
	}

	/* Error handling */
	at91_stop_hc(pdev);

 err:
	usb_put_hcd(hcd);
	return retval;
}