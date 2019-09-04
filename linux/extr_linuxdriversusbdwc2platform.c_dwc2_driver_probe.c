#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {scalar_t__ start; } ;
struct TYPE_8__ {int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; } ;
struct platform_device {TYPE_1__ dev; } ;
struct dwc2_hsotg {int irq; scalar_t__ dr_mode; int gadget_enabled; int hcd_enabled; scalar_t__ hibernated; int /*<<< orphan*/  needs_byte_swap; TYPE_1__* dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_DR_MODE_HOST ; 
 scalar_t__ USB_DR_MODE_PERIPHERAL ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct dwc2_hsotg* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dwc2_hsotg*) ; 
 int dma_set_coherent_mask (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_check_core_endianness (struct dwc2_hsotg*) ; 
 int dwc2_core_reset (struct dwc2_hsotg*,int) ; 
 int /*<<< orphan*/  dwc2_debugfs_init (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_force_dr_mode (struct dwc2_hsotg*) ; 
 int dwc2_gadget_init (struct dwc2_hsotg*) ; 
 int dwc2_get_dr_mode (struct dwc2_hsotg*) ; 
 int dwc2_get_hwparams (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_handle_common_intr ; 
 int dwc2_hcd_init (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_hsotg_remove (struct dwc2_hsotg*) ; 
 int dwc2_init_params (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_lowlevel_hw_disable (struct dwc2_hsotg*) ; 
 int dwc2_lowlevel_hw_enable (struct dwc2_hsotg*) ; 
 int dwc2_lowlevel_hw_init (struct dwc2_hsotg*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dwc2_driver_probe(struct platform_device *dev)
{
	struct dwc2_hsotg *hsotg;
	struct resource *res;
	int retval;

	hsotg = devm_kzalloc(&dev->dev, sizeof(*hsotg), GFP_KERNEL);
	if (!hsotg)
		return -ENOMEM;

	hsotg->dev = &dev->dev;

	/*
	 * Use reasonable defaults so platforms don't have to provide these.
	 */
	if (!dev->dev.dma_mask)
		dev->dev.dma_mask = &dev->dev.coherent_dma_mask;
	retval = dma_set_coherent_mask(&dev->dev, DMA_BIT_MASK(32));
	if (retval) {
		dev_err(&dev->dev, "can't set coherent DMA mask: %d\n", retval);
		return retval;
	}

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	hsotg->regs = devm_ioremap_resource(&dev->dev, res);
	if (IS_ERR(hsotg->regs))
		return PTR_ERR(hsotg->regs);

	dev_dbg(&dev->dev, "mapped PA %08lx to VA %p\n",
		(unsigned long)res->start, hsotg->regs);

	retval = dwc2_lowlevel_hw_init(hsotg);
	if (retval)
		return retval;

	spin_lock_init(&hsotg->lock);

	hsotg->irq = platform_get_irq(dev, 0);
	if (hsotg->irq < 0) {
		dev_err(&dev->dev, "missing IRQ resource\n");
		return hsotg->irq;
	}

	dev_dbg(hsotg->dev, "registering common handler for irq%d\n",
		hsotg->irq);
	retval = devm_request_irq(hsotg->dev, hsotg->irq,
				  dwc2_handle_common_intr, IRQF_SHARED,
				  dev_name(hsotg->dev), hsotg);
	if (retval)
		return retval;

	retval = dwc2_lowlevel_hw_enable(hsotg);
	if (retval)
		return retval;

	hsotg->needs_byte_swap = dwc2_check_core_endianness(hsotg);

	retval = dwc2_get_dr_mode(hsotg);
	if (retval)
		goto error;

	/*
	 * Reset before dwc2_get_hwparams() then it could get power-on real
	 * reset value form registers.
	 */
	retval = dwc2_core_reset(hsotg, false);
	if (retval)
		goto error;

	/* Detect config values from hardware */
	retval = dwc2_get_hwparams(hsotg);
	if (retval)
		goto error;

	/*
	 * For OTG cores, set the force mode bits to reflect the value
	 * of dr_mode. Force mode bits should not be touched at any
	 * other time after this.
	 */
	dwc2_force_dr_mode(hsotg);

	retval = dwc2_init_params(hsotg);
	if (retval)
		goto error;

	if (hsotg->dr_mode != USB_DR_MODE_HOST) {
		retval = dwc2_gadget_init(hsotg);
		if (retval)
			goto error;
		hsotg->gadget_enabled = 1;
	}

	if (hsotg->dr_mode != USB_DR_MODE_PERIPHERAL) {
		retval = dwc2_hcd_init(hsotg);
		if (retval) {
			if (hsotg->gadget_enabled)
				dwc2_hsotg_remove(hsotg);
			goto error;
		}
		hsotg->hcd_enabled = 1;
	}

	platform_set_drvdata(dev, hsotg);
	hsotg->hibernated = 0;

	dwc2_debugfs_init(hsotg);

	/* Gadget code manages lowlevel hw on its own */
	if (hsotg->dr_mode == USB_DR_MODE_PERIPHERAL)
		dwc2_lowlevel_hw_disable(hsotg);

	return 0;

error:
	dwc2_lowlevel_hw_disable(hsotg);
	return retval;
}