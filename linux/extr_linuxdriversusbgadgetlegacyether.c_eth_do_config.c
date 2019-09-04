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
struct usb_configuration {TYPE_1__* cdev; int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  descriptors; } ;
struct TYPE_2__ {int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_CONFIG_ATT_WAKEUP ; 
 scalar_t__ can_support_ecm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_ecm ; 
 int /*<<< orphan*/  f_eem ; 
 int /*<<< orphan*/  f_geth ; 
 int /*<<< orphan*/  fi_ecm ; 
 int /*<<< orphan*/  fi_eem ; 
 int /*<<< orphan*/  fi_geth ; 
 scalar_t__ gadget_is_otg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_desc ; 
 int usb_add_function (struct usb_configuration*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_function (int /*<<< orphan*/ ) ; 
 scalar_t__ use_eem ; 

__attribute__((used)) static int eth_do_config(struct usb_configuration *c)
{
	int status = 0;

	/* FIXME alloc iConfiguration string, set it in c->strings */

	if (gadget_is_otg(c->cdev->gadget)) {
		c->descriptors = otg_desc;
		c->bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	}

	if (use_eem) {
		f_eem = usb_get_function(fi_eem);
		if (IS_ERR(f_eem))
			return PTR_ERR(f_eem);

		status = usb_add_function(c, f_eem);
		if (status < 0)
			usb_put_function(f_eem);

		return status;
	} else if (can_support_ecm(c->cdev->gadget)) {
		f_ecm = usb_get_function(fi_ecm);
		if (IS_ERR(f_ecm))
			return PTR_ERR(f_ecm);

		status = usb_add_function(c, f_ecm);
		if (status < 0)
			usb_put_function(f_ecm);

		return status;
	} else {
		f_geth = usb_get_function(fi_geth);
		if (IS_ERR(f_geth))
			return PTR_ERR(f_geth);

		status = usb_add_function(c, f_geth);
		if (status < 0)
			usb_put_function(f_geth);

		return status;
	}

}