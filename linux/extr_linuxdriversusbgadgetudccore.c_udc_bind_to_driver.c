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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * driver; int /*<<< orphan*/  kobj; } ;
struct usb_udc {TYPE_2__* gadget; TYPE_4__ dev; struct usb_gadget_driver* driver; } ;
struct usb_gadget_driver {int (* bind ) (TYPE_2__*,struct usb_gadget_driver*) ;int /*<<< orphan*/  function; int /*<<< orphan*/  (* unbind ) (TYPE_2__*) ;int /*<<< orphan*/  max_speed; int /*<<< orphan*/  driver; } ;
struct TYPE_6__ {int /*<<< orphan*/ * driver; } ;
struct TYPE_7__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int EISNAM ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  dev_dbg (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,struct usb_gadget_driver*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_gadget_udc_set_speed (struct usb_udc*,int /*<<< orphan*/ ) ; 
 int usb_gadget_udc_start (struct usb_udc*) ; 
 int /*<<< orphan*/  usb_udc_connect_control (struct usb_udc*) ; 

__attribute__((used)) static int udc_bind_to_driver(struct usb_udc *udc, struct usb_gadget_driver *driver)
{
	int ret;

	dev_dbg(&udc->dev, "registering UDC driver [%s]\n",
			driver->function);

	udc->driver = driver;
	udc->dev.driver = &driver->driver;
	udc->gadget->dev.driver = &driver->driver;

	usb_gadget_udc_set_speed(udc, driver->max_speed);

	ret = driver->bind(udc->gadget, driver);
	if (ret)
		goto err1;
	ret = usb_gadget_udc_start(udc);
	if (ret) {
		driver->unbind(udc->gadget);
		goto err1;
	}
	usb_udc_connect_control(udc);

	kobject_uevent(&udc->dev.kobj, KOBJ_CHANGE);
	return 0;
err1:
	if (ret != -EISNAM)
		dev_err(&udc->dev, "failed to start %s: %d\n",
			udc->driver->function, ret);
	udc->driver = NULL;
	udc->dev.driver = NULL;
	udc->gadget->dev.driver = NULL;
	return ret;
}