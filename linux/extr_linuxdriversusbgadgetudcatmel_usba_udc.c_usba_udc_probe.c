#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ep_list; } ;
struct usba_udc {int irq; int num_ep; struct clk* usba_ep; TYPE_1__ gadget; struct platform_device* pdev; int /*<<< orphan*/ * vbus_pin; struct clk* hclk; struct clk* pclk; int /*<<< orphan*/  vbus_mutex; int /*<<< orphan*/  lock; struct clk* fifo; struct clk* regs; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  CTRL_IOMEM_ID ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FIFO_IOMEM_ID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  USBA_DISABLE_MASK ; 
 int /*<<< orphan*/  USBA_VBUS_IRQFLAGS ; 
 struct clk* atmel_udc_of_init (struct platform_device*,struct usba_udc*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,struct resource*,struct clk*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct usba_udc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct usba_udc*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct usba_udc*) ; 
 int /*<<< orphan*/  gpiod_to_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_status_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct usba_udc*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toggle_bias (struct usba_udc*,int /*<<< orphan*/ ) ; 
 int usb_add_gadget_udc (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  usba_ep_init_debugfs (struct usba_udc*,struct clk*) ; 
 TYPE_1__ usba_gadget_template ; 
 int /*<<< orphan*/  usba_init_debugfs (struct usba_udc*) ; 
 int /*<<< orphan*/  usba_udc_irq ; 
 int /*<<< orphan*/  usba_vbus_irq_thread ; 
 int /*<<< orphan*/  usba_writel (struct usba_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usba_udc_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct clk *pclk, *hclk;
	struct usba_udc *udc;
	int irq, ret, i;

	udc = devm_kzalloc(&pdev->dev, sizeof(*udc), GFP_KERNEL);
	if (!udc)
		return -ENOMEM;

	udc->gadget = usba_gadget_template;
	INIT_LIST_HEAD(&udc->gadget.ep_list);

	res = platform_get_resource(pdev, IORESOURCE_MEM, CTRL_IOMEM_ID);
	udc->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(udc->regs))
		return PTR_ERR(udc->regs);
	dev_info(&pdev->dev, "MMIO registers at %pR mapped at %p\n",
		 res, udc->regs);

	res = platform_get_resource(pdev, IORESOURCE_MEM, FIFO_IOMEM_ID);
	udc->fifo = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(udc->fifo))
		return PTR_ERR(udc->fifo);
	dev_info(&pdev->dev, "FIFO at %pR mapped at %p\n", res, udc->fifo);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	pclk = devm_clk_get(&pdev->dev, "pclk");
	if (IS_ERR(pclk))
		return PTR_ERR(pclk);
	hclk = devm_clk_get(&pdev->dev, "hclk");
	if (IS_ERR(hclk))
		return PTR_ERR(hclk);

	spin_lock_init(&udc->lock);
	mutex_init(&udc->vbus_mutex);
	udc->pdev = pdev;
	udc->pclk = pclk;
	udc->hclk = hclk;

	platform_set_drvdata(pdev, udc);

	/* Make sure we start from a clean slate */
	ret = clk_prepare_enable(pclk);
	if (ret) {
		dev_err(&pdev->dev, "Unable to enable pclk, aborting.\n");
		return ret;
	}

	usba_writel(udc, CTRL, USBA_DISABLE_MASK);
	clk_disable_unprepare(pclk);

	udc->usba_ep = atmel_udc_of_init(pdev, udc);

	toggle_bias(udc, 0);

	if (IS_ERR(udc->usba_ep))
		return PTR_ERR(udc->usba_ep);

	ret = devm_request_irq(&pdev->dev, irq, usba_udc_irq, 0,
				"atmel_usba_udc", udc);
	if (ret) {
		dev_err(&pdev->dev, "Cannot request irq %d (error %d)\n",
			irq, ret);
		return ret;
	}
	udc->irq = irq;

	if (udc->vbus_pin) {
		irq_set_status_flags(gpiod_to_irq(udc->vbus_pin), IRQ_NOAUTOEN);
		ret = devm_request_threaded_irq(&pdev->dev,
				gpiod_to_irq(udc->vbus_pin), NULL,
				usba_vbus_irq_thread, USBA_VBUS_IRQFLAGS,
				"atmel_usba_udc", udc);
		if (ret) {
			udc->vbus_pin = NULL;
			dev_warn(&udc->pdev->dev,
				 "failed to request vbus irq; "
				 "assuming always on\n");
		}
	}

	ret = usb_add_gadget_udc(&pdev->dev, &udc->gadget);
	if (ret)
		return ret;
	device_init_wakeup(&pdev->dev, 1);

	usba_init_debugfs(udc);
	for (i = 1; i < udc->num_ep; i++)
		usba_ep_init_debugfs(udc, &udc->usba_ep[i]);

	return 0;
}