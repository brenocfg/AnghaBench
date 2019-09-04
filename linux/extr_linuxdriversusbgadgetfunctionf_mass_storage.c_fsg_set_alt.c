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
struct usb_function {int dummy; } ;
struct fsg_dev {TYPE_1__* common; } ;
struct TYPE_2__ {struct fsg_dev* new_fsg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSG_STATE_CONFIG_CHANGE ; 
 int USB_GADGET_DELAYED_STATUS ; 
 struct fsg_dev* fsg_from_func (struct usb_function*) ; 
 int /*<<< orphan*/  raise_exception (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsg_set_alt(struct usb_function *f, unsigned intf, unsigned alt)
{
	struct fsg_dev *fsg = fsg_from_func(f);
	fsg->common->new_fsg = fsg;
	raise_exception(fsg->common, FSG_STATE_CONFIG_CHANGE);
	return USB_GADGET_DELAYED_STATUS;
}