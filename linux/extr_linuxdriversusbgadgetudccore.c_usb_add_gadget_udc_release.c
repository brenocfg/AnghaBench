#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void (* release ) (struct device*) ;struct device* parent; int /*<<< orphan*/  groups; int /*<<< orphan*/  class; } ;
struct usb_udc {int vbus; TYPE_1__ dev; int /*<<< orphan*/  list; struct usb_gadget* gadget; } ;
struct usb_gadget {TYPE_1__ dev; struct usb_udc* udc; int /*<<< orphan*/  work; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_STATE_NOTATTACHED ; 
 int check_pending_gadget_drivers (struct usb_udc*) ; 
 int dev_set_name (TYPE_1__*,char*,...) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_del (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  kobject_name (int /*<<< orphan*/ *) ; 
 struct usb_udc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  udc_class ; 
 int /*<<< orphan*/  udc_list ; 
 int /*<<< orphan*/  udc_lock ; 
 int /*<<< orphan*/  usb_gadget_set_state (struct usb_gadget*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_gadget_state_work ; 
 int /*<<< orphan*/  usb_udc_attr_groups ; 
 void usb_udc_nop_release (struct device*) ; 
 void usb_udc_release (struct device*) ; 

int usb_add_gadget_udc_release(struct device *parent, struct usb_gadget *gadget,
		void (*release)(struct device *dev))
{
	struct usb_udc		*udc;
	int			ret = -ENOMEM;

	dev_set_name(&gadget->dev, "gadget");
	INIT_WORK(&gadget->work, usb_gadget_state_work);
	gadget->dev.parent = parent;

	if (release)
		gadget->dev.release = release;
	else
		gadget->dev.release = usb_udc_nop_release;

	device_initialize(&gadget->dev);

	udc = kzalloc(sizeof(*udc), GFP_KERNEL);
	if (!udc)
		goto err_put_gadget;

	device_initialize(&udc->dev);
	udc->dev.release = usb_udc_release;
	udc->dev.class = udc_class;
	udc->dev.groups = usb_udc_attr_groups;
	udc->dev.parent = parent;
	ret = dev_set_name(&udc->dev, "%s", kobject_name(&parent->kobj));
	if (ret)
		goto err_put_udc;

	ret = device_add(&gadget->dev);
	if (ret)
		goto err_put_udc;

	udc->gadget = gadget;
	gadget->udc = udc;

	mutex_lock(&udc_lock);
	list_add_tail(&udc->list, &udc_list);

	ret = device_add(&udc->dev);
	if (ret)
		goto err_unlist_udc;

	usb_gadget_set_state(gadget, USB_STATE_NOTATTACHED);
	udc->vbus = true;

	/* pick up one of pending gadget drivers */
	ret = check_pending_gadget_drivers(udc);
	if (ret)
		goto err_del_udc;

	mutex_unlock(&udc_lock);

	return 0;

 err_del_udc:
	device_del(&udc->dev);

 err_unlist_udc:
	list_del(&udc->list);
	mutex_unlock(&udc_lock);

	device_del(&gadget->dev);

 err_put_udc:
	put_device(&udc->dev);

 err_put_gadget:
	put_device(&gadget->dev);
	return ret;
}