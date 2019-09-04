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
struct usb_ep {int dummy; } ;
struct usb_endpoint_descriptor {int dummy; } ;

/* Variables and functions */
 struct usb_ep* usb_ep_autoconfig_ss (struct usb_gadget*,struct usb_endpoint_descriptor*,int /*<<< orphan*/ *) ; 

struct usb_ep *usb_ep_autoconfig(
	struct usb_gadget		*gadget,
	struct usb_endpoint_descriptor	*desc
)
{
	return usb_ep_autoconfig_ss(gadget, desc, NULL);
}