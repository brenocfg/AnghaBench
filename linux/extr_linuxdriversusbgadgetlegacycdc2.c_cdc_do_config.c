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
struct usb_configuration {int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  descriptors; TYPE_1__* cdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_CONFIG_ATT_WAKEUP ; 
 int /*<<< orphan*/  f_acm ; 
 int /*<<< orphan*/  f_ecm ; 
 int /*<<< orphan*/  fi_ecm ; 
 int /*<<< orphan*/  fi_serial ; 
 scalar_t__ gadget_is_otg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_desc ; 
 int usb_add_function (struct usb_configuration*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_remove_function (struct usb_configuration*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdc_do_config(struct usb_configuration *c)
{
	int	status;

	if (gadget_is_otg(c->cdev->gadget)) {
		c->descriptors = otg_desc;
		c->bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	}

	f_ecm = usb_get_function(fi_ecm);
	if (IS_ERR(f_ecm)) {
		status = PTR_ERR(f_ecm);
		goto err_get_ecm;
	}

	status = usb_add_function(c, f_ecm);
	if (status)
		goto err_add_ecm;

	f_acm = usb_get_function(fi_serial);
	if (IS_ERR(f_acm)) {
		status = PTR_ERR(f_acm);
		goto err_get_acm;
	}

	status = usb_add_function(c, f_acm);
	if (status)
		goto err_add_acm;
	return 0;

err_add_acm:
	usb_put_function(f_acm);
err_get_acm:
	usb_remove_function(c, f_ecm);
err_add_ecm:
	usb_put_function(f_ecm);
err_get_ecm:
	return status;
}