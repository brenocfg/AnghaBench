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
struct usb_host_endpoint {struct cvmx_usb_pipe* hcpriv; } ;
struct TYPE_2__ {struct device* controller; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct octeon_hcd {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;
struct cvmx_usb_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cvmx_usb_cancel_all (struct octeon_hcd*,struct cvmx_usb_pipe*) ; 
 scalar_t__ cvmx_usb_close_pipe (struct octeon_hcd*,struct cvmx_usb_pipe*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct cvmx_usb_pipe*) ; 
 struct octeon_hcd* hcd_to_octeon (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void octeon_usb_endpoint_disable(struct usb_hcd *hcd,
					struct usb_host_endpoint *ep)
{
	struct device *dev = hcd->self.controller;

	if (ep->hcpriv) {
		struct octeon_hcd *usb = hcd_to_octeon(hcd);
		struct cvmx_usb_pipe *pipe = ep->hcpriv;
		unsigned long flags;

		spin_lock_irqsave(&usb->lock, flags);
		cvmx_usb_cancel_all(usb, pipe);
		if (cvmx_usb_close_pipe(usb, pipe))
			dev_dbg(dev, "Closing pipe %p failed\n", pipe);
		spin_unlock_irqrestore(&usb->lock, flags);
		ep->hcpriv = NULL;
	}
}