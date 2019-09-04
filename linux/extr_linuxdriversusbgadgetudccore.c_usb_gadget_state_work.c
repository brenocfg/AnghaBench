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
struct work_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct usb_udc {TYPE_1__ dev; } ;
struct usb_gadget {struct usb_udc* udc; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct usb_gadget* work_to_gadget (struct work_struct*) ; 

__attribute__((used)) static void usb_gadget_state_work(struct work_struct *work)
{
	struct usb_gadget *gadget = work_to_gadget(work);
	struct usb_udc *udc = gadget->udc;

	if (udc)
		sysfs_notify(&udc->dev.kobj, NULL, "state");
}