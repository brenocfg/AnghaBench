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
struct usb_host_endpoint {int /*<<< orphan*/  desc; } ;
struct urb {int /*<<< orphan*/  pipe; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__* pipetypes ; 
 size_t usb_endpoint_type (int /*<<< orphan*/ *) ; 
 struct usb_host_endpoint* usb_pipe_endpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipetype (int /*<<< orphan*/ ) ; 

int usb_urb_ep_type_check(const struct urb *urb)
{
	const struct usb_host_endpoint *ep;

	ep = usb_pipe_endpoint(urb->dev, urb->pipe);
	if (!ep)
		return -EINVAL;
	if (usb_pipetype(urb->pipe) != pipetypes[usb_endpoint_type(&ep->desc)])
		return -EINVAL;
	return 0;
}