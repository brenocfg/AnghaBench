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
struct usb_host_endpoint {int dummy; } ;
struct usb_device {struct usb_host_endpoint** ep_out; struct usb_host_endpoint** ep_in; } ;
struct urb {int /*<<< orphan*/  pipe; struct usb_device* dev; } ;

/* Variables and functions */
 int usb_pipeendpoint (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 

inline struct usb_host_endpoint *dwc_urb_to_endpoint(struct urb *urb)
{
	struct usb_device *dev = urb->dev;
	int ep_num = usb_pipeendpoint(urb->pipe);

	if (usb_pipein(urb->pipe))
		return dev->ep_in[ep_num];
	else
		return dev->ep_out[ep_num];
}