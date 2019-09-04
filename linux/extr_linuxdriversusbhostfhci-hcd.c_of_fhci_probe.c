#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {struct device* controller; } ;
struct usb_hcd {TYPE_4__* regs; TYPE_1__ self; int /*<<< orphan*/  power_budget; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct fhci_hcd {int* gpios; int* alow_gpios; scalar_t__ fullspeed_clk; scalar_t__ lowspeed_clk; TYPE_2__** pins; TYPE_2__* timer; TYPE_4__* regs; int /*<<< orphan*/  pram; } ;
struct device_node {int dummy; } ;
typedef  enum of_gpio_flags { ____Placeholder_of_gpio_flags } of_gpio_flags ;
struct TYPE_12__ {int /*<<< orphan*/  usb_usbmr; int /*<<< orphan*/  usb_usber; } ;
struct TYPE_11__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FHCI_PORT_FULL ; 
 int /*<<< orphan*/  FHCI_PORT_LOW ; 
 int /*<<< orphan*/  FHCI_PORT_POWER_OFF ; 
 int /*<<< orphan*/  FHCI_PRAM_SIZE ; 
 int GPIO_SPEED ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 scalar_t__ IS_ERR_VALUE (unsigned long) ; 
 unsigned int NO_IRQ ; 
 int NUM_GPIOS ; 
 int NUM_PINS ; 
 int OF_GPIO_ACTIVE_LOW ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  QE_ASSIGN_PAGE_TO_DEVICE ; 
 scalar_t__ QE_CLK_DUMMY ; 
 scalar_t__ QE_CLK_NONE ; 
 int /*<<< orphan*/  QE_CR_PROTOCOL_UNSPECIFIED ; 
 int /*<<< orphan*/  QE_CR_SUBBLOCK_USB ; 
 int USB_CLOCK ; 
 int /*<<< orphan*/  cpm_muram_addr (unsigned long) ; 
 unsigned long cpm_muram_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpm_muram_free (unsigned long) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct usb_hcd*) ; 
 int /*<<< orphan*/  device_wakeup_enable (struct device*) ; 
 int /*<<< orphan*/  fhci_config_transceiver (struct fhci_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fhci_dfs_create (struct fhci_hcd*) ; 
 int /*<<< orphan*/  fhci_driver ; 
 int /*<<< orphan*/  fhci_frame_limit_timer_irq ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct usb_hcd*) ; 
 int gpio_direction_output (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int gpio_request (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* gtm_get_timer16 () ; 
 int /*<<< orphan*/  gtm_put_timer16 (TYPE_2__*) ; 
 struct fhci_hcd* hcd_to_fhci (struct usb_hcd*) ; 
 TYPE_4__* ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (TYPE_4__*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (unsigned int) ; 
 unsigned int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int of_get_gpio_flags (struct device_node*,int,int*) ; 
 void* of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int) ; 
 void* qe_clock_source (char const*) ; 
 int /*<<< orphan*/  qe_issue_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  qe_pin_free (TYPE_2__*) ; 
 TYPE_2__* qe_pin_request (struct device_node*,int) ; 
 int /*<<< orphan*/  qe_usb_clock_set (scalar_t__,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct usb_hcd*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int usb_add_hcd (struct usb_hcd*,unsigned int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_disabled () ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int of_fhci_probe(struct platform_device *ofdev)
{
	struct device *dev = &ofdev->dev;
	struct device_node *node = dev->of_node;
	struct usb_hcd *hcd;
	struct fhci_hcd *fhci;
	struct resource usb_regs;
	unsigned long pram_addr;
	unsigned int usb_irq;
	const char *sprop;
	const u32 *iprop;
	int size;
	int ret;
	int i;
	int j;

	if (usb_disabled())
		return -ENODEV;

	sprop = of_get_property(node, "mode", NULL);
	if (sprop && strcmp(sprop, "host"))
		return -ENODEV;

	hcd = usb_create_hcd(&fhci_driver, dev, dev_name(dev));
	if (!hcd) {
		dev_err(dev, "could not create hcd\n");
		return -ENOMEM;
	}

	fhci = hcd_to_fhci(hcd);
	hcd->self.controller = dev;
	dev_set_drvdata(dev, hcd);

	iprop = of_get_property(node, "hub-power-budget", &size);
	if (iprop && size == sizeof(*iprop))
		hcd->power_budget = *iprop;

	/* FHCI registers. */
	ret = of_address_to_resource(node, 0, &usb_regs);
	if (ret) {
		dev_err(dev, "could not get regs\n");
		goto err_regs;
	}

	hcd->regs = ioremap(usb_regs.start, resource_size(&usb_regs));
	if (!hcd->regs) {
		dev_err(dev, "could not ioremap regs\n");
		ret = -ENOMEM;
		goto err_regs;
	}
	fhci->regs = hcd->regs;

	/* Parameter RAM. */
	iprop = of_get_property(node, "reg", &size);
	if (!iprop || size < sizeof(*iprop) * 4) {
		dev_err(dev, "can't get pram offset\n");
		ret = -EINVAL;
		goto err_pram;
	}

	pram_addr = cpm_muram_alloc(FHCI_PRAM_SIZE, 64);
	if (IS_ERR_VALUE(pram_addr)) {
		dev_err(dev, "failed to allocate usb pram\n");
		ret = -ENOMEM;
		goto err_pram;
	}

	qe_issue_cmd(QE_ASSIGN_PAGE_TO_DEVICE, QE_CR_SUBBLOCK_USB,
		     QE_CR_PROTOCOL_UNSPECIFIED, pram_addr);
	fhci->pram = cpm_muram_addr(pram_addr);

	/* GPIOs and pins */
	for (i = 0; i < NUM_GPIOS; i++) {
		int gpio;
		enum of_gpio_flags flags;

		gpio = of_get_gpio_flags(node, i, &flags);
		fhci->gpios[i] = gpio;
		fhci->alow_gpios[i] = flags & OF_GPIO_ACTIVE_LOW;

		if (!gpio_is_valid(gpio)) {
			if (i < GPIO_SPEED) {
				dev_err(dev, "incorrect GPIO%d: %d\n",
					i, gpio);
				goto err_gpios;
			} else {
				dev_info(dev, "assuming board doesn't have "
					"%s gpio\n", i == GPIO_SPEED ?
					"speed" : "power");
				continue;
			}
		}

		ret = gpio_request(gpio, dev_name(dev));
		if (ret) {
			dev_err(dev, "failed to request gpio %d", i);
			goto err_gpios;
		}

		if (i >= GPIO_SPEED) {
			ret = gpio_direction_output(gpio, 0);
			if (ret) {
				dev_err(dev, "failed to set gpio %d as "
					"an output\n", i);
				i++;
				goto err_gpios;
			}
		}
	}

	for (j = 0; j < NUM_PINS; j++) {
		fhci->pins[j] = qe_pin_request(node, j);
		if (IS_ERR(fhci->pins[j])) {
			ret = PTR_ERR(fhci->pins[j]);
			dev_err(dev, "can't get pin %d: %d\n", j, ret);
			goto err_pins;
		}
	}

	/* Frame limit timer and its interrupt. */
	fhci->timer = gtm_get_timer16();
	if (IS_ERR(fhci->timer)) {
		ret = PTR_ERR(fhci->timer);
		dev_err(dev, "failed to request qe timer: %i", ret);
		goto err_get_timer;
	}

	ret = request_irq(fhci->timer->irq, fhci_frame_limit_timer_irq,
			  0, "qe timer (usb)", hcd);
	if (ret) {
		dev_err(dev, "failed to request timer irq");
		goto err_timer_irq;
	}

	/* USB Host interrupt. */
	usb_irq = irq_of_parse_and_map(node, 0);
	if (usb_irq == NO_IRQ) {
		dev_err(dev, "could not get usb irq\n");
		ret = -EINVAL;
		goto err_usb_irq;
	}

	/* Clocks. */
	sprop = of_get_property(node, "fsl,fullspeed-clock", NULL);
	if (sprop) {
		fhci->fullspeed_clk = qe_clock_source(sprop);
		if (fhci->fullspeed_clk == QE_CLK_DUMMY) {
			dev_err(dev, "wrong fullspeed-clock\n");
			ret = -EINVAL;
			goto err_clocks;
		}
	}

	sprop = of_get_property(node, "fsl,lowspeed-clock", NULL);
	if (sprop) {
		fhci->lowspeed_clk = qe_clock_source(sprop);
		if (fhci->lowspeed_clk == QE_CLK_DUMMY) {
			dev_err(dev, "wrong lowspeed-clock\n");
			ret = -EINVAL;
			goto err_clocks;
		}
	}

	if (fhci->fullspeed_clk == QE_CLK_NONE &&
			fhci->lowspeed_clk == QE_CLK_NONE) {
		dev_err(dev, "no clocks specified\n");
		ret = -EINVAL;
		goto err_clocks;
	}

	dev_info(dev, "at 0x%p, irq %d\n", hcd->regs, usb_irq);

	fhci_config_transceiver(fhci, FHCI_PORT_POWER_OFF);

	/* Start with full-speed, if possible. */
	if (fhci->fullspeed_clk != QE_CLK_NONE) {
		fhci_config_transceiver(fhci, FHCI_PORT_FULL);
		qe_usb_clock_set(fhci->fullspeed_clk, USB_CLOCK);
	} else {
		fhci_config_transceiver(fhci, FHCI_PORT_LOW);
		qe_usb_clock_set(fhci->lowspeed_clk, USB_CLOCK >> 3);
	}

	/* Clear and disable any pending interrupts. */
	out_be16(&fhci->regs->usb_usber, 0xffff);
	out_be16(&fhci->regs->usb_usbmr, 0);

	ret = usb_add_hcd(hcd, usb_irq, 0);
	if (ret < 0)
		goto err_add_hcd;

	device_wakeup_enable(hcd->self.controller);

	fhci_dfs_create(fhci);

	return 0;

err_add_hcd:
err_clocks:
	irq_dispose_mapping(usb_irq);
err_usb_irq:
	free_irq(fhci->timer->irq, hcd);
err_timer_irq:
	gtm_put_timer16(fhci->timer);
err_get_timer:
err_pins:
	while (--j >= 0)
		qe_pin_free(fhci->pins[j]);
err_gpios:
	while (--i >= 0) {
		if (gpio_is_valid(fhci->gpios[i]))
			gpio_free(fhci->gpios[i]);
	}
	cpm_muram_free(pram_addr);
err_pram:
	iounmap(hcd->regs);
err_regs:
	usb_put_hcd(hcd);
	return ret;
}