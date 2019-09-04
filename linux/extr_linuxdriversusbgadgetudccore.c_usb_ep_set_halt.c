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
struct usb_ep {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set_halt ) (struct usb_ep*,int) ;} ;

/* Variables and functions */
 int stub1 (struct usb_ep*,int) ; 
 int /*<<< orphan*/  trace_usb_ep_set_halt (struct usb_ep*,int) ; 

int usb_ep_set_halt(struct usb_ep *ep)
{
	int ret;

	ret = ep->ops->set_halt(ep, 1);
	trace_usb_ep_set_halt(ep, ret);

	return ret;
}