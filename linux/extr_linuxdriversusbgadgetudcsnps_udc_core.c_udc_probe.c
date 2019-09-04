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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_4__ {int /*<<< orphan*/  max_speed; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/ * ops; } ;
struct udc {int irq; scalar_t__ chiprev; TYPE_1__* regs; TYPE_2__ gadget; int /*<<< orphan*/  dev; int /*<<< orphan*/  phys_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_BIT (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  UDC_DEVCTL_SD ; 
 int /*<<< orphan*/  UDC_DRIVER_VERSION_STRING ; 
 scalar_t__ UDC_HSA0_REV ; 
 scalar_t__ UDC_HSB1_REV ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gadget_release ; 
 char* mod_desc ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  print_regs (struct udc*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  startup_registers (struct udc*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct udc* udc ; 
 int /*<<< orphan*/  udc_ops ; 
 int /*<<< orphan*/  udc_pollstall_timer ; 
 int /*<<< orphan*/  udc_pollstall_timer_function ; 
 int /*<<< orphan*/  udc_timer ; 
 int /*<<< orphan*/  udc_timer_function ; 
 int usb_add_gadget_udc_release (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int udc_probe(struct udc *dev)
{
	char		tmp[128];
	u32		reg;
	int		retval;

	/* device struct setup */
	dev->gadget.ops = &udc_ops;

	dev_set_name(&dev->gadget.dev, "gadget");
	dev->gadget.name = name;
	dev->gadget.max_speed = USB_SPEED_HIGH;

	/* init registers, interrupts, ... */
	startup_registers(dev);

	dev_info(dev->dev, "%s\n", mod_desc);

	snprintf(tmp, sizeof(tmp), "%d", dev->irq);

	/* Print this device info for AMD chips only*/
	if (dev->chiprev == UDC_HSA0_REV ||
	    dev->chiprev == UDC_HSB1_REV) {
		dev_info(dev->dev, "irq %s, pci mem %08lx, chip rev %02x(Geode5536 %s)\n",
			 tmp, dev->phys_addr, dev->chiprev,
			 (dev->chiprev == UDC_HSA0_REV) ?
			 "A0" : "B1");
		strcpy(tmp, UDC_DRIVER_VERSION_STRING);
		if (dev->chiprev == UDC_HSA0_REV) {
			dev_err(dev->dev, "chip revision is A0; too old\n");
			retval = -ENODEV;
			goto finished;
		}
		dev_info(dev->dev,
			 "driver version: %s(for Geode5536 B1)\n", tmp);
	}

	udc = dev;

	retval = usb_add_gadget_udc_release(udc->dev, &dev->gadget,
					    gadget_release);
	if (retval)
		goto finished;

	/* timer init */
	timer_setup(&udc_timer, udc_timer_function, 0);
	timer_setup(&udc_pollstall_timer, udc_pollstall_timer_function, 0);

	/* set SD */
	reg = readl(&dev->regs->ctl);
	reg |= AMD_BIT(UDC_DEVCTL_SD);
	writel(reg, &dev->regs->ctl);

	/* print dev register info */
	print_regs(dev);

	return 0;

finished:
	return retval;
}