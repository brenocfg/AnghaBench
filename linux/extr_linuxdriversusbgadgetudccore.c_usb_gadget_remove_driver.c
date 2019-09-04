#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * driver; int /*<<< orphan*/  kobj; } ;
struct usb_udc {TYPE_3__* gadget; TYPE_6__ dev; TYPE_2__* driver; } ;
struct TYPE_7__ {int /*<<< orphan*/ * driver; } ;
struct TYPE_9__ {TYPE_1__ dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* unbind ) (TYPE_3__*) ;int /*<<< orphan*/  (* disconnect ) (TYPE_3__*) ;int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  dev_dbg (TYPE_6__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_gadget_disconnect (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_gadget_udc_stop (struct usb_udc*) ; 

__attribute__((used)) static void usb_gadget_remove_driver(struct usb_udc *udc)
{
	dev_dbg(&udc->dev, "unregistering UDC driver [%s]\n",
			udc->driver->function);

	kobject_uevent(&udc->dev.kobj, KOBJ_CHANGE);

	usb_gadget_disconnect(udc->gadget);
	udc->driver->disconnect(udc->gadget);
	udc->driver->unbind(udc->gadget);
	usb_gadget_udc_stop(udc);

	udc->driver = NULL;
	udc->dev.driver = NULL;
	udc->gadget->dev.driver = NULL;
}