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
struct usb_ep {int dummy; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct renesas_usb3_ep {int dummy; } ;

/* Variables and functions */
 int usb3_enable_pipe_n (struct renesas_usb3_ep*,struct usb_endpoint_descriptor const*) ; 
 struct renesas_usb3_ep* usb_ep_to_usb3_ep (struct usb_ep*) ; 

__attribute__((used)) static int renesas_usb3_ep_enable(struct usb_ep *_ep,
				  const struct usb_endpoint_descriptor *desc)
{
	struct renesas_usb3_ep *usb3_ep = usb_ep_to_usb3_ep(_ep);

	return usb3_enable_pipe_n(usb3_ep, desc);
}