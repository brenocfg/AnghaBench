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
struct zero_dev {int dummy; } ;
struct usb_request {int /*<<< orphan*/  complete; } ;
struct usb_ep {int /*<<< orphan*/  name; struct zero_dev* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct zero_dev*,char*,int /*<<< orphan*/ ,int) ; 
 struct usb_request* alloc_ep_req (struct usb_ep*,int) ; 
 int /*<<< orphan*/  free_ep_req (struct usb_ep*,struct usb_request*) ; 
 int usb_ep_queue (struct usb_ep*,struct usb_request*,int) ; 
 int /*<<< orphan*/  zero_isoc_complete ; 

__attribute__((used)) static struct usb_request *
zero_start_isoc_ep (struct usb_ep *ep, int gfp_flags)
{
	struct usb_request	*req;
	int			status;

	req = alloc_ep_req (ep, 512);
	if (!req)
		return NULL;

	req->complete = zero_isoc_complete;

	status = usb_ep_queue (ep, req, gfp_flags);
	if (status) {
		struct zero_dev	*dev = ep->driver_data;

		ERROR (dev, "start %s --> %d\n", ep->name, status);
		free_ep_req (ep, req);
		req = NULL;
	}

	return req;
}