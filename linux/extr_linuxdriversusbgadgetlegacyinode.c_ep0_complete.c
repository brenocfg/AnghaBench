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
struct usb_request {scalar_t__ status; int /*<<< orphan*/  complete; int /*<<< orphan*/ * buf; } ;
struct usb_ep {struct dev_data* driver_data; } ;
struct dev_data {int setup_out_error; int setup_out_ready; int /*<<< orphan*/  lock; int /*<<< orphan*/  rbuf; int /*<<< orphan*/  setup_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  clean_req (struct usb_ep*,struct usb_request*) ; 
 int /*<<< orphan*/  ep0_readable (struct dev_data*) ; 
 int /*<<< orphan*/  epio_complete ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ep0_complete (struct usb_ep *ep, struct usb_request *req)
{
	struct dev_data		*dev = ep->driver_data;
	unsigned long		flags;
	int			free = 1;

	/* for control OUT, data must still get to userspace */
	spin_lock_irqsave(&dev->lock, flags);
	if (!dev->setup_in) {
		dev->setup_out_error = (req->status != 0);
		if (!dev->setup_out_error)
			free = 0;
		dev->setup_out_ready = 1;
		ep0_readable (dev);
	}

	/* clean up as appropriate */
	if (free && req->buf != &dev->rbuf)
		clean_req (ep, req);
	req->complete = epio_complete;
	spin_unlock_irqrestore(&dev->lock, flags);
}