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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * bus; } ;
struct usb_gadget_driver {TYPE_1__ driver; } ;
struct usb_gadget {int dummy; } ;
struct fotg210_udc {scalar_t__ reg; struct usb_gadget_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMCR_GLINT_EN ; 
 scalar_t__ FOTG210_DMCR ; 
 struct fotg210_udc* gadget_to_fotg210 (struct usb_gadget*) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int fotg210_udc_start(struct usb_gadget *g,
		struct usb_gadget_driver *driver)
{
	struct fotg210_udc *fotg210 = gadget_to_fotg210(g);
	u32 value;

	/* hook up the driver */
	driver->driver.bus = NULL;
	fotg210->driver = driver;

	/* enable device global interrupt */
	value = ioread32(fotg210->reg + FOTG210_DMCR);
	value |= DMCR_GLINT_EN;
	iowrite32(value, fotg210->reg + FOTG210_DMCR);

	return 0;
}