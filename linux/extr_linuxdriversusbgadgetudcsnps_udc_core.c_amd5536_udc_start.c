#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/ * bus; } ;
struct usb_gadget_driver {TYPE_4__ driver; } ;
struct usb_gadget {int dummy; } ;
struct udc {TYPE_3__* regs; TYPE_2__* ep; struct usb_gadget_driver* driver; } ;
struct TYPE_7__ {int /*<<< orphan*/  ctl; } ;
struct TYPE_5__ {int /*<<< orphan*/  driver_data; } ;
struct TYPE_6__ {TYPE_1__ ep; } ;

/* Variables and functions */
 int AMD_CLEAR_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDC_DEVCTL_SD ; 
 size_t UDC_EP0IN_IX ; 
 size_t UDC_EP0OUT_IX ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_ep0 (struct udc*) ; 
 struct udc* to_amd5536_udc (struct usb_gadget*) ; 
 int /*<<< orphan*/  usb_connect (struct udc*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amd5536_udc_start(struct usb_gadget *g,
		struct usb_gadget_driver *driver)
{
	struct udc *dev = to_amd5536_udc(g);
	u32 tmp;

	driver->driver.bus = NULL;
	dev->driver = driver;

	/* Some gadget drivers use both ep0 directions.
	 * NOTE: to gadget driver, ep0 is just one endpoint...
	 */
	dev->ep[UDC_EP0OUT_IX].ep.driver_data =
		dev->ep[UDC_EP0IN_IX].ep.driver_data;

	/* get ready for ep0 traffic */
	setup_ep0(dev);

	/* clear SD */
	tmp = readl(&dev->regs->ctl);
	tmp = tmp & AMD_CLEAR_BIT(UDC_DEVCTL_SD);
	writel(tmp, &dev->regs->ctl);

	usb_connect(dev);

	return 0;
}