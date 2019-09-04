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
struct usb_ep {int enabled; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* disable ) (struct usb_ep*) ;} ;

/* Variables and functions */
 int stub1 (struct usb_ep*) ; 
 int /*<<< orphan*/  trace_usb_ep_disable (struct usb_ep*,int) ; 

int usb_ep_disable(struct usb_ep *ep)
{
	int ret = 0;

	if (!ep->enabled)
		goto out;

	ret = ep->ops->disable(ep);
	if (ret)
		goto out;

	ep->enabled = false;

out:
	trace_usb_ep_disable(ep, ret);

	return ret;
}