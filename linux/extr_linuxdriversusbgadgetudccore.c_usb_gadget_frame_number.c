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
struct usb_gadget {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_frame ) (struct usb_gadget*) ;} ;

/* Variables and functions */
 int stub1 (struct usb_gadget*) ; 
 int /*<<< orphan*/  trace_usb_gadget_frame_number (struct usb_gadget*,int) ; 

int usb_gadget_frame_number(struct usb_gadget *gadget)
{
	int ret;

	ret = gadget->ops->get_frame(gadget);

	trace_usb_gadget_frame_number(gadget, ret);

	return ret;
}