#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_gadget {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int usb_add_gadget_udc_release (struct device*,struct usb_gadget*,int /*<<< orphan*/ *) ; 

int usb_add_gadget_udc(struct device *parent, struct usb_gadget *gadget)
{
	return usb_add_gadget_udc_release(parent, gadget, NULL);
}