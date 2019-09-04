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
struct usbhsh_hpriv {int dummy; } ;
struct usbhsh_ep {int dummy; } ;
struct usbhsh_device {int dummy; } ;
struct usb_host_endpoint {int dummy; } ;
struct usb_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbhsh_device_detach (struct usbhsh_hpriv*,struct usbhsh_device*) ; 
 int /*<<< orphan*/  usbhsh_device_has_endpoint (struct usbhsh_device*) ; 
 int /*<<< orphan*/  usbhsh_endpoint_detach (struct usbhsh_hpriv*,struct usb_host_endpoint*) ; 
 struct usbhsh_ep* usbhsh_ep_to_uep (struct usb_host_endpoint*) ; 
 struct usbhsh_hpriv* usbhsh_hcd_to_hpriv (struct usb_hcd*) ; 
 struct usbhsh_device* usbhsh_uep_to_udev (struct usbhsh_ep*) ; 

__attribute__((used)) static void usbhsh_endpoint_disable(struct usb_hcd *hcd,
				    struct usb_host_endpoint *ep)
{
	struct usbhsh_ep *uep = usbhsh_ep_to_uep(ep);
	struct usbhsh_device *udev;
	struct usbhsh_hpriv *hpriv;

	/*
	 * this function might be called manytimes by same hcd/ep
	 * in-endpoint == out-endpoint if ep == dcp.
	 */
	if (!uep)
		return;

	udev	= usbhsh_uep_to_udev(uep);
	hpriv	= usbhsh_hcd_to_hpriv(hcd);

	usbhsh_endpoint_detach(hpriv, ep);

	/*
	 * if there is no endpoint,
	 * free device
	 */
	if (!usbhsh_device_has_endpoint(udev))
		usbhsh_device_detach(hpriv, udev);
}