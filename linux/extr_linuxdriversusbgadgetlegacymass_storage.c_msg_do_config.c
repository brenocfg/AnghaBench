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
struct fsg_opts {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_CONFIG_ATT_WAKEUP ; 
 int /*<<< orphan*/  f_msg ; 
 int /*<<< orphan*/  fi_msg ; 
 struct fsg_opts* fsg_opts_from_func_inst (int /*<<< orphan*/ ) ; 
 scalar_t__ gadget_is_otg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_desc ; 
 int usb_add_function (struct usb_configuration*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_function (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msg_do_config(struct usb_configuration *c)
{
	struct fsg_opts *opts;
	int ret;

	if (gadget_is_otg(c->cdev->gadget)) {
		c->descriptors = otg_desc;
		c->bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	}

	opts = fsg_opts_from_func_inst(fi_msg);

	f_msg = usb_get_function(fi_msg);
	if (IS_ERR(f_msg))
		return PTR_ERR(f_msg);

	ret = usb_add_function(c, f_msg);
	if (ret)
		goto put_func;

	return 0;

put_func:
	usb_put_function(f_msg);
	return ret;
}